#ifndef ECPPS_CONCURRENTQUEUE_HPP
#define ECPPS_CONCURRENTQUEUE_HPP

#include <concurrentqueue/blockingconcurrentqueue.h>
#include <atomic>

class Worker;

using Task = std::function<void()>;

struct ConcurrentQueue : public moodycamel::BlockingConcurrentQueue<Task>
{
public:
    std::atomic<std::size_t> m_pendingTasks{0u};
};

#endif //ECPPS_CONCURRENTQUEUE_HPP
