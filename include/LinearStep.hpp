#ifndef ECPPS_LINEARSTEP_HPP
#define ECPPS_LINEARSTEP_HPP

#include <Step.hpp>

class LinearStep : public Step
{
public:
    LinearStep() = default;
    virtual ~LinearStep() = default;
    virtual void run() override;
};

#endif //ECPPS_LINEARSTEP_HPP
