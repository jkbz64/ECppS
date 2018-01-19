#ifndef ECPPS_STEP_HPP
#define ECPPS_STEP_HPP

#include <sol/forward.hpp>
#include <functional>
#include <vector>

class Context;
class SystemDef;
class System;

using SystemPair = std::tuple<std::reference_wrapper<System>, sol::variadic_args>;

class Step
{
public:
    Step() = default;
    virtual ~Step() = default;
    virtual void run(Context&) = 0;
    
    void process(const SystemDef&, sol::variadic_args);
protected:
    std::vector<std::function<SystemPair(Context&)>> m_actions;
};

#endif //ECPPS_STEP_HPP
