#ifndef ECPPS_WORKER_HPP
#define ECPPS_WORKER_HPP

#include <concurrentqueue/blockingconcurrentqueue.h>
#include <sol/state.hpp>
#include <list>
#include <ConcurrentStep/ConcurrentQueue.hpp>

class ConcurrentQueue;

class Worker
{
public:
    enum class State
    {
        unitinialized,
        running,
        stopped,
        finished
    };
    Worker(ConcurrentQueue&);
    ~Worker();
    
    void start(std::atomic<std::size_t>&);
    void stop();
    void join();
private:
    void run();
    friend class ThreadPool;
    friend class ConcurrentStep;
    std::thread m_thread;
    ConcurrentQueue& m_queue;
    std::atomic<State> m_state{State::unitinialized};
};

#endif //ECPPS_WORKER_HPP
