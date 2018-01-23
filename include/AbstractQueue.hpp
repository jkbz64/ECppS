#ifndef ECPPS_ABSTRACTQUEUE_HPP
#define ECPPS_ABSTRACTQUEUE_HPP

class Task;

class AbstractQueue
{
public:
    AbstractQueue() = default;
    virtual ~AbstractQueue() = default;
    
    virtual void enqueue(Task) = 0;
    virtual void waitDequeue(Task&) = 0;
};

#endif
