#include <LinearStep/LinearStep.hpp>
#include <Context.hpp>

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
}

