#include <ConcurrentStep/Worker.hpp>
#include <ConcurrentStep/ConcurrentQueue.hpp>
#include <iostream>

Worker::Worker(std::shared_ptr<ConcurrentQueue> queue) :
    m_queue(queue)
{

}

Worker::~Worker() = default;

void Worker::start()
{
    m_thread = std::thread([this]{
        m_state = State::running;
        run();
    });
}

void Worker::stop()
{
    m_state = State::stopped;
}

void Worker::run()
{
    Task task;
    //Probably always running
    auto& pendingTasks = m_queue->getPendingTasks();
    while(m_state == State::running)
    {
        m_queue->waitDequeue(task);
        if(task.m_function())
            pendingTasks.fetch_add(-1, std::memory_order_release);
        else
        {
            m_queue->enqueue(task);
            pendingTasks.fetch_add(-1, std::memory_order_release);
        }
    }
    m_state = State::finished;
}
