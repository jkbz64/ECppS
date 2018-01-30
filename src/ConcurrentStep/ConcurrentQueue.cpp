#include <ConcurrentStep/ConcurrentQueue.hpp>

ConcurrentQueue::ConcurrentQueue() :
    m_pendingTasks(0)
{

}

ConcurrentQueue::~ConcurrentQueue()
{

}

void ConcurrentQueue::enqueue(Task task)
{
    m_pendingTasks.fetch_add(1, std::memory_order_release);
    m_queue.enqueue(task);
}

void ConcurrentQueue::waitDequeue(Task &task)
{
    m_queue.wait_dequeue(task);
}

std::atomic<int>& ConcurrentQueue::getPendingTasks()
{
    return m_pendingTasks;
}
