#include <LinearStep/LinearStep.hpp>
#include <Context.hpp>
#include <iostream>

LinearStep::LinearStep() :
    Step(nullptr) /////////// TODO
{

}

void LinearStep::run(Context& context)
{
    for(auto& system : m_chain)
    {
        m_context->getSystem(system).process();
    }
    m_chain.clear();
}

