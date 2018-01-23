#include <ConcurrentStep/ConcurrentStep.hpp>
#include <ConcurrentStep/ConcurrentQueue.hpp>

ConcurrentStep::ConcurrentStep() :
    Step(new ConcurrentQueue()),
    m_pool(1, std::dynamic_pointer_cast<ConcurrentQueue>(m_queue))
{

}

void ConcurrentStep::run(Context &context)
{
    auto concQueue = dynamic_cast<ConcurrentQueue*>(m_queue.get());
    for(auto& task : m_tasks)
        task();
    
    while(concQueue->getPendingTasks().load(std::memory_order_acquire) > 0)
        continue;
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
}