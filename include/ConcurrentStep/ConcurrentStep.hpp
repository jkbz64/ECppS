#ifndef ECPPS_CONCURRENTSTEP_HPP
#define ECPPS_CONCURRENTSTEP_HPP

#include <Step.hpp>
#include <ConcurrentStep/ThreadPool.hpp>
#include <sol/state_view.hpp>
#include <sol/thread.hpp>

using DoneSystems = std::unordered_map<SystemDef, std::atomic<bool>, SystemDef::Hasher, SystemDef::Comparator>;
using CachedTasks = std::unordered_map<SystemDef, std::vector<Task>, SystemDef::Hasher, SystemDef::Comparator>;

class ConcurrentStep : public Step
{
public:
    ConcurrentStep(sol::this_state);
    virtual ~ConcurrentStep() = default;
    virtual void process(const SystemDef&);
protected:
    void rebuildTasks();
    sol::this_state L;
    ConcurrentQueue m_queue;
    ThreadPool m_pool;
    std::vector<sol::thread> m_stacks;
    DoneSystems m_doneSystems;
    CachedTasks m_cachedTasks;
};

#endif //ECPPS_CONCURRENTSTEP_HPP
