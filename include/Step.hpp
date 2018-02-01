#ifndef ECPPS_STEP_HPP
#define ECPPS_STEP_HPP

#include <sol/forward.hpp>
#include <fwd.hpp>
#include <atomic>
#include <SystemDef.hpp>
#include <AbstractQueue.hpp>
#include <memory>

using SystemChain = std::vector<SystemDef>;

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
    SystemChain m_chain;
    std::shared_ptr<AbstractQueue> m_queue;
};

#endif //ECPPS_STEP_HPP
