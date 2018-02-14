#include <System.hpp>

System::System(sol::this_state L, const SystemDef& def) :
    m_main(L)
{
    m_properties = sol::table::create(L.lua_state());
}