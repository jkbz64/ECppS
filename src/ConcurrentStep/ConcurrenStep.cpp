#include <ConcurrentStep/ConcurrentStep.hpp>
#include <ConcurrentStep/ConcurrentQueue.hpp>
#include <Context.hpp>

ConcurrentStep::ConcurrentStep() :
    Step(new ConcurrentQueue()),
    m_pool(std::thread::hardware_concurrency(), std::dynamic_pointer_cast<ConcurrentQueue>(m_queue))
{

}

void ConcurrentStep::run(Context &context)
{
    std::unordered_map<SystemDef, std::atomic<bool>, SystemDef::Hasher, SystemDef::Comparator> doneSystems;
    auto concQueue = dynamic_cast<ConcurrentQueue*>(m_queue.get());
    
    for(auto& system : m_chain)
    {
        doneSystems[system].store(false);
        concQueue->enqueue([&doneSystems, &system = m_context->getSystem(system)]()
        {
            const auto& dependencies = system.def().dependencies();
            if(!dependencies.empty())
            {
               while(true)
               {
                   retry:
                   
                   for(const auto& dependency : dependencies)
                   {
                       if(!doneSystems[dependency].load())
                         goto retry;
                   }
                   break;
               }
            }
            system.process();
            doneSystems[system.def()].store(true);
        });
    }
    
    while(concQueue->getPendingTasks().load() > 0)
        continue;
}