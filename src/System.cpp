#include <System.hpp>
#include <SystemDef.hpp>
#include <iostream>

System::System(const SystemDef& def) :
    m_def(def)
{

}

void System::process(sol::variadic_args args)
{
    std::cout << m_def.id() << std::endl;
}
