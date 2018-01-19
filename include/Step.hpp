#ifndef ECPPS_STEP_HPP
#define ECPPS_STEP_HPP

class Step
{
public:
    Step() = default;
    virtual ~Step() = default;
    virtual void run() = 0;
};

#endif //ECPPS_STEP_HPP
