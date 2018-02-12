#ifndef ECPPS_CONCURRENTQUEUE_HPP
#define ECPPS_CONCURRENTQUEUE_HPP

#include <concurrentqueue/blockingconcurrentqueue.h>
#include <atomic>

class Worker;

using Task = std::function<void(Worker&)>;

struct ConcurrentQueue : public moodycamel::BlockingConcurrentQueue<Task>
{
public:
    std::atomic<int> m_pendingTasks{0};
};

#endif //ECPPS_CONCURRENTQUEUE_HPP
