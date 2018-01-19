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

}
