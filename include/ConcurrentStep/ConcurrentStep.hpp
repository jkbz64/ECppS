#ifndef ECPPS_CONCURRENTSTEP_HPP
#define ECPPS_CONCURRENTSTEP_HPP

#include <Step.hpp>
#include <ConcurrentStep/ThreadPool.hpp>

class ConcurrentStep : public Step
{
public:
    ConcurrentStep();
    virtual ~ConcurrentStep() = default;
    virtual void run(Context&) override;
protected:
    ThreadPool m_pool;
};

#endif //ECPPS_CONCURRENTSTEP_HPP
