#include <ConcurrentStep/ConcurrentStep.hpp>
#include <ConcurrentStep/ConcurrentQueue.hpp>
#include <Context.hpp>
#include <iostream>
#include <ConcurrentStep/Worker.hpp>
#include <sol.hpp>

ConcurrentStep::ConcurrentStep(sol::this_state l) :
        L(l),
        m_queue(),
        m_pool(l, std::thread::hardware_concurrency(), m_queue)
{
    for(auto& stack : m_stacks)
        stack = sol::thread::create(L);
}

void ConcurrentStep::process(const SystemDef &def)
{
    if(updateCache(def))
        rebuildTasks();
    
    auto& tasksChain = m_cachedTasks[def];
    
    m_queue.m_pendingTasks.fetch_add(tasksChain.size(), std::memory_order_release);
    m_queue.enqueue_bulk(tasksChain.begin(), tasksChain.size());
    
    while(m_queue.m_pendingTasks.load(std::memory_order_acquire) > 0u)
        continue;
}

void ConcurrentStep::rebuildTasks()
{
    m_nextStack = 0u;
    m_refHolder.clear();
    m_cachedTasks.clear();
    m_objs.clear();
    for(auto& cachedChain : m_cachedChains)
    {
        auto& tasks = m_cachedTasks[cachedChain.first];
        auto& systems = cachedChain.second;
        for(auto& def : systems)
        {
            m_doneSystems.emplace(def, false);
            const auto& currentStack = m_stacks[m_nextStack++];
            m_refHolder.emplace_back(currentStack.thread_state(), def.m_process);
            m_objs.emplace_back(sol::make_reference(currentStack.thread_state(), std::ref(m_context->getSystem(def))));
            m_context->getSystem(def).m_threadProperties = sol::table(currentStack.thread_state(), m_context->getSystem(def).m_properties);
            tasks.emplace_back([this, &def, &process = m_refHolder.back(), &system = m_objs.back()]()
                               {
                                   for(const auto& dependency : def.dependencies())
                                   {
                                       while(!m_doneSystems[dependency].load(std::memory_order_acquire))
                                           continue;
                                   }
                                   process.call(system);
                                   m_doneSystems[def].store(true, std::memory_order_release);
                               });
        }
    }
}
