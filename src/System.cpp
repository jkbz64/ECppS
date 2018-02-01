#include <System.hpp>
#include <SystemDef.hpp>
#include <thread>

System::System(const SystemDef& def) :
    m_def(def)
{

}

void System::process()
{

}

const SystemDef &System::def() const
{
    return m_def;
}
