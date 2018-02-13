#include <ConcurrentStep/ConcurrentStep.hpp>
#include <ConcurrentStep/ConcurrentQueue.hpp>
#include <Context.hpp>
#include <iostream>
#include <ConcurrentStep/Worker.hpp>
#include <sol.hpp>

ConcurrentStep::ConcurrentStep(sol::this_state l) :
        L(l),
        m_pool(l, std::thread::hardware_concurrency(), m_queue)
{
    for(auto i = 0u; i < std::thread::hardware_concurrency() * 2; ++i)
        m_stacks.emplace_back(sol::thread::create(L));
}

/*void ConcurrentStep::run(Context &context)
{
    std::unordered_map<SystemDef, std::atomic<bool>, SystemDef::Hasher, SystemDef::Comparator> doneSystems;
    
    std::vector<Task> tasks;
    std::list<sol::function> fcs;
    
    std::size_t tID = 0u;
    for(auto& def : m_chain)
    {
        doneSystems.emplace(def, false);
        fcs.emplace_back(m_stacks[tID].thread_state(), def.m_process);
        tasks.emplace_back([&doneSystems, &system = context.getSystem(def), &moved = fcs.back()]()
                           {
                               for(const auto& dependency : system.def().dependencies())
                               {
                                   while(!doneSystems[dependency].load(std::memory_order_acquire))
                                       continue;
                               }
                               moved.call();
                               doneSystems[system.def()].store(true, std::memory_order_release);
                           });
        ++tID;
        tID = tID % (std::thread::hardware_concurrency() * 2);
    }
    
    m_queue.m_pendingTasks.fetch_add(tasks.size(), std::memory_order_relaxed);
    m_queue.enqueue_bulk(tasks.begin(), tasks.size());
    
    while(m_queue.m_pendingTasks.load(std::memory_order_acquire) > 0)
        continue;
    
    m_chain.clear();
}*/

void ConcurrentStep::process(const SystemDef &def)
{
    if(updateCache(def))
        rebuildTasks();
    
    auto& tasksChain = m_cachedTasks[def];
    
    m_queue.m_pendingTasks.fetch_add(tasksChain.size(), std::memory_order_relaxed);
    m_queue.enqueue_bulk(tasksChain.begin(), tasksChain.size());
    
    while(m_queue.m_pendingTasks.load(std::memory_order_acquire) > 0)
        continue;
}

void ConcurrentStep::rebuildTasks()
{
    m_cachedTasks.clear();
    for(auto& cachedChain : m_cachedChains)
    {
        auto& tasks = m_cachedTasks[cachedChain.first];
        auto& systems = cachedChain.second;
        for(const auto& system : systems)
        {
            m_doneSystems.emplace(system, false);
            tasks.emplace_back([this, system]()
                               {
                                   for(const auto& dependency : system.dependencies())
                                   {
                                       while(!m_doneSystems[dependency].load(std::memory_order_acquire))
                                           continue;
                                   }
                                   m_doneSystems[system].store(true, std::memory_order_release);
                               });
        }
    }
}
