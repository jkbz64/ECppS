#ifndef ECPPS_LINEARSTEP_HPP
#define ECPPS_LINEARSTEP_HPP

#include <Step.hpp>
#include <sol/variadic_args.hpp>
#include <SystemDef.hpp>

class LinearStep : public Step
{
public:
    LinearStep() = default;
    virtual ~LinearStep() = default;
    virtual void run(Context&) override;
};

#endif //ECPPS_LINEARSTEP_HPP
