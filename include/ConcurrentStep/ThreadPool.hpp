#ifndef ECPPS_THREADPOOL_HPP
#define ECPPS_THREADPOOL_HPP

#include <cstddef>
#include <vector>
#include <concurrentqueue/blockingconcurrentqueue.h>
#include <sol/forward.hpp>
#include <ConcurrentStep/ConcurrentQueue.hpp>

class Worker;

class ThreadPool
{
public:
    ThreadPool(sol::this_state, std::size_t, ConcurrentQueue&);
    ~ThreadPool();
    
    bool allFinished();
private:
    friend class ConcurrentStep;
    std::vector <std::unique_ptr<Worker>> m_workers;
    ConcurrentQueue& m_queue;
    std::atomic<std::size_t> m_unitinializedCount;
};

#endif //ECPPS_THREADPOOL_HPP
