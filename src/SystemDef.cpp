#include <SystemDef.hpp>
#include <ComponentDef.hpp>
#include <System.hpp>

SystemDef::SystemDef()
{
    static std::size_t counter = 0u;
    m_ID = counter++;
}

const std::size_t& SystemDef::id() const
{
    return m_ID;
}

SystemDef& SystemDef::read(const ComponentDef &def)
{
    m_reads.emplace(def.id());
    return *this;
}

SystemDef& SystemDef::write(const ComponentDef &def)
{
    m_writes.emplace(def.id());
    return *this;
}

SystemDef& SystemDef::depends(const SystemDef &def)
{
    m_dependencies.emplace(def.id());
    return *this;
}

SystemDef& SystemDef::init(sol::function f)
{
    m_init = f;
    return *this;
}

SystemDef& SystemDef::process(sol::function f)
{
    
    return *this;
}

std::size_t SystemDef::Hasher::operator()(const SystemDef &def) const
{
    return def.m_ID;
}
