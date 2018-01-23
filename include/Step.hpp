#ifndef ECPPS_STEP_HPP
#define ECPPS_STEP_HPP

#include <sol/forward.hpp>
#include <fwd.hpp>
#include <atomic>
#include <SystemDef.hpp>
#include <AbstractQueue.hpp>

using DoneSystems = std::map<SystemDef, std::atomic<bool>, SystemDef::Less>;

class Step
{
public:
    Step(AbstractQueue*);
    virtual ~Step();
    virtual void run(Context&) = 0;
    void process(const SystemDef&);
protected:
    friend class Context;
    Context* m_context{nullptr};
    std::shared_ptr<AbstractQueue> m_queue;
    std::vector<std::function<void()>> m_tasks;
    DoneSystems m_doneSystems;
};

#endif //ECPPS_STEP_HPP
