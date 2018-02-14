#ifndef ECPPS_SYSTEM_HPP
#define ECPPS_SYSTEM_HPP

#include <sol/table.hpp>
#include <SystemDef.hpp>

class System
{
public:
    System(sol::this_state L, const SystemDef&);
private:
    sol::this_state m_main;
    friend class ECppS;
    friend class ConcurrentStep;
    friend class LinearStep;
    sol::table m_properties;
    sol::table m_threadProperties;
};

#endif //ECPPS_SYSTEM_HPP
