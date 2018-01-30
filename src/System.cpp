#include <System.hpp>
#include <SystemDef.hpp>
#include <iostream>

System::System(const SystemDef& def) :
    m_def(def)
{

}

void System::process()
{
    //std::cout << m_def.id() << std::endl;
}

const SystemDef &System::def() const
{
    return m_def;
}
