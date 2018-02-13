#ifndef ECPPS_STEP_HPP
#define ECPPS_STEP_HPP

#include <sol/forward.hpp>
#include <fwd.hpp>
#include <atomic>
#include <SystemDef.hpp>
#include <memory>

using SystemChain = std::vector<SystemDef>;
using CachedChains = std::unordered_map<SystemDef, SystemChain, SystemDef::Hasher, SystemDef::Comparator>;

class Step
{
public:
    Step();
    virtual ~Step();
    virtual void process(const SystemDef&) = 0;
protected:
    bool updateCache(const SystemDef&);
    friend class Context;
    Context* m_context{nullptr};
    CachedChains m_cachedChains;
};

#endif //ECPPS_STEP_HPP
