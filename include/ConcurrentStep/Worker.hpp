#ifndef ECPPS_WORKER_HPP
#define ECPPS_WORKER_HPP

#include <concurrentqueue/blockingconcurrentqueue.h>

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
    Worker(std::shared_ptr<ConcurrentQueue>);
    ~Worker();
    
    void start(std::atomic<std::size_t>&);
    void stop();
    void join();
private:
    void run();
    friend class ThreadPool;
    std::thread m_thread;
    std::shared_ptr<ConcurrentQueue> m_queue;
    std::atomic<State> m_state{State::unitinialized};
};

#endif //ECPPS_WORKER_HPP
