#include <System.hpp>
#include <SystemDef.hpp>
#include <thread>

System::System(const SystemDef& def) :
    m_def(def)
{
    m_process = def.m_process;
}

const SystemDef &System::def() const
{
    return m_def;
}
