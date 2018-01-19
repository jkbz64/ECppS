#include <Context.hpp>
#include <LinearStep.hpp>

Context::Context() :
        m_systems(),
        m_step(new LinearStep())
{

}

Context::~Context() = default;

void Context::addSystem(const SystemDef &def)
{
    if(m_systems.find(def) == std::end(m_systems))
        m_systems.emplace(def, System());
    else
        throw std::runtime_error("Trying to add already existing system to context");
}

void Context::removeSystem(const SystemDef &def)
{
    if(m_systems.find(def) == std::end(m_systems))
        throw std::runtime_error("Trying to remove non existing system");
    else
        m_systems.erase(def);
}

System& Context::getSystem(const SystemDef &def)
{
    if(m_systems.find(def) == std::end(m_systems))
        throw std::runtime_error("Trying to retrieve non existing system");
    else
        return m_systems[def];
}

/*
 * context:step(function(step)
 *      step:process(MovementSystem, dt)
 *      step:process(function() window:clear(255, 255, 255, 255) end)
 *      step:
 *
 * end)
 */


void Context::step(sol::function f)
{
    f.call(this);
    m_step->run(*this);
}

