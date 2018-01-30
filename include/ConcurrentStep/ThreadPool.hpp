#ifndef ECPPS_THREADPOOL_HPP
#define ECPPS_THREADPOOL_HPP

#include <cstddef>
#include <vector>
#include <concurrentqueue/blockingconcurrentqueue.h>
#include <ConcurrentStep/ConcurrentQueue.hpp>

class Worker;

class ThreadPool
{
public:
    ThreadPool(std::size_t, std::shared_ptr<ConcurrentQueue>);
    ~ThreadPool();
    
    bool allFinished();
private:
    std::vector <std::unique_ptr<Worker>> m_workers;
    std::shared_ptr<ConcurrentQueue> m_queue;
};

#endif //ECPPS_THREADPOOL_HPP
