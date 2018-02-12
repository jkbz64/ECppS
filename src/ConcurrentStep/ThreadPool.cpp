#include <ConcurrentStep/ThreadPool.hpp>
#include <ConcurrentStep/Worker.hpp>

ThreadPool::ThreadPool(sol::this_state L, std::size_t n, ConcurrentQueue& queue) :
    m_queue(queue)
{
    m_unitinializedCount = n;
    for(auto i = 0u; i < n; ++i)
    {
        m_workers.emplace_back(std::move(std::make_unique<Worker>(queue)));
        m_workers[i]->start(m_unitinializedCount);
    }
}

ThreadPool::~ThreadPool()
{
    while(m_unitinializedCount.load() > 0)
        continue;
    
    for(auto &worker : m_workers)
        worker->stop();
    
    while(!allFinished())
        m_queue.enqueue([](Worker&){});
    
    for(auto &worker : m_workers)
        worker->join();
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