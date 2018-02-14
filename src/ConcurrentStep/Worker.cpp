#include <ConcurrentStep/Worker.hpp>
#include <ConcurrentStep/ConcurrentQueue.hpp>
#include <iostream>

Worker::Worker(ConcurrentQueue& queue) :
    m_queue(queue)
{

}

Worker::~Worker() = default;

void Worker::start(std::atomic<std::size_t>& uninitializedCount)
{
    m_thread = std::thread([this, &uninitializedCount]{
        m_state = State::running;
        --uninitializedCount;
        run();
    });
}

void Worker::stop()
{
    m_state = State::stopped;
}

void Worker::run()
{
    auto& pendingTasks = m_queue.m_pendingTasks;
    while(m_state == State::running)
    {
        m_queue.wait_dequeue(m_task);
        m_task();
        pendingTasks.fetch_sub(1u, std::memory_order_release);
    }
    m_state = State::finished;
}

void Worker::join()
{
    m_thread.join();
}