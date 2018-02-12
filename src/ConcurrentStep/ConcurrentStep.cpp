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

void ConcurrentStep::run(Context &context)
{
    std::unordered_map<SystemDef, std::atomic<bool>, SystemDef::Hasher, SystemDef::Comparator> doneSystems;
    
    std::vector<Task> tasks;
    std::list<sol::function> fcs;
    
    std::size_t tID = 0u;
    for(auto& def : m_chain)
    {
        doneSystems.emplace(def, false);
        fcs.emplace_back(m_stacks[tID].thread_state(), def.m_process);
        tasks.emplace_back([&doneSystems, &system = context.getSystem(def), &moved = fcs.back()](Worker& worker)
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
}