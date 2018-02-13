#include <Context.hpp>
#include <ConcurrentStep/ConcurrentStep.hpp>
#include <LinearStep/LinearStep.hpp>

Context::Context() :
        m_systems(),
        m_step(nullptr)
{

}

Context::~Context() = default;

void Context::addSystem(const SystemDef &def, sol::variadic_args args)
{
    if(m_systems.find(def) == std::end(m_systems))
    {
        auto system = System(def);
        def.m_init(system, args);
        m_systems.emplace(def, std::move(system));
    }
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
        return m_systems.at(def);
}

bool Context::hasSystem(const SystemDef &def)
{
    return m_systems.find(def) != std::end(m_systems);
}

void Context::step(sol::function f)
{
    f.call(m_step.get());
}

void Context::setStep(std::unique_ptr<Step>& step)
{
    m_step = std::move(step);
    m_step->m_context = this;
}

