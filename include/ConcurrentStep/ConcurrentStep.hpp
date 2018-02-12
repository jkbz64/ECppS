#ifndef ECPPS_CONCURRENTSTEP_HPP
#define ECPPS_CONCURRENTSTEP_HPP

#include <Step.hpp>
#include <ConcurrentStep/ThreadPool.hpp>
#include <sol/state_view.hpp>
#include <sol/thread.hpp>

class ConcurrentStep : public Step
{
public:
    ConcurrentStep(sol::this_state);
    virtual ~ConcurrentStep() = default;
    virtual void run(Context&) override;
protected:
    sol::this_state L;
    ConcurrentQueue m_queue;
    ThreadPool m_pool;
    std::vector<sol::thread> m_stacks;
};

#endif //ECPPS_CONCURRENTSTEP_HPP
