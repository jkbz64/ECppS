#include <ConcurrentStep/ThreadPool.hpp>
#include <ConcurrentStep/Worker.hpp>

ThreadPool::ThreadPool(std::size_t n, std::shared_ptr<ConcurrentQueue> queue) :
    m_queue(queue)
{
    for(auto i = 0u; i < n; ++i)
    {
        m_workers.emplace_back(std::move(std::make_unique<Worker>(queue)));
        m_workers[i]->start();
    }
    
    //TODO remove
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

ThreadPool::~ThreadPool()
{
    for(auto &worker : m_workers)
        worker->stop();
    
    while(!allFinished())
        m_queue->enqueue([](){});
    
    for(auto &worker : m_workers)
        worker->m_thread.join();
    
}

bool ThreadPool::allFinished()
{
    for(auto &worker : m_workers)
    {
        if(worker->m_state != Worker::State::finished)
            return false;
    }
    return true;
}