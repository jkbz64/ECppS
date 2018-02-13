#ifndef ECPPS_LINEARSTEP_HPP
#define ECPPS_LINEARSTEP_HPP

#include <Step.hpp>
#include <sol/variadic_args.hpp>
#include <SystemDef.hpp>

class LinearStep : public Step
{
public:
    LinearStep();
    virtual ~LinearStep() = default;
    virtual void process(const SystemDef&) override;
};

#endif //ECPPS_LINEARSTEP_HPP
