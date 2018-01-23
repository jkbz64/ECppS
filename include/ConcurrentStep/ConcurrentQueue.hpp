#ifndef ECPPS_CONCURRENTQUEUE_HPP
#define ECPPS_CONCURRENTQUEUE_HPP

#include <AbstractQueue.hpp>
#include <concurrentqueue/blockingconcurrentqueue.h>
#include <atomic>
#include <Task.hpp>

class ConcurrentQueue : public AbstractQueue
{
public:
    ConcurrentQueue();
    virtual ~ConcurrentQueue();
    
    virtual void enqueue(Task) override;
    virtual void waitDequeue(Task&) override;
    
    std::atomic<int>& getPendingTasks();
protected:
    moodycamel::BlockingConcurrentQueue<Task> m_queue;
    std::atomic<int> m_pendingTasks;
};

#endif //ECPPS_CONCURRENTQUEUE_HPP
