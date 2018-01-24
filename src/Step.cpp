#include <Step.hpp>
#include <sol/variadic_args.hpp>
#include <Context.hpp>
#include <Task.hpp>

namespace
{

}

Step::Step(AbstractQueue* queue) :
    m_queue(queue)
{

}

Step::~Step() = default;

void Step::process(const SystemDef &def)
{
    if(m_context->hasSystem(def))
    {
        m_doneSystems[def].store(false);
        auto& system = m_context->getSystem(def);
        for(auto& dep : def.m_dependencies)
            process(dep);
    
        m_tasks.emplace_back([doneSystems = std::reference_wrapper<DoneSystems>(m_doneSystems), this, &system]()
        {
            m_queue->enqueue(Task(system, doneSystems, sol::variadic_args()));
        });
    }
    else
        throw std::runtime_error("Trying to process system which doesn't exist in context");
}

