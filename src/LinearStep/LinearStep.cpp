#include <LinearStep/LinearStep.hpp>
#include <Context.hpp>

LinearStep::LinearStep()
{

}

void LinearStep::run(Context& context)
{
    for(auto& system : m_chain)
        m_context->getSystem(system).m_process.call();
    m_chain.clear();
}

