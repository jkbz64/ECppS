#include <System.hpp>
#include <SystemDef.hpp>

System::System(const SystemDef& def) :
    m_def(def)
{

}

void System::process(sol::variadic_args args)
{
    m_def.m_process();
}
