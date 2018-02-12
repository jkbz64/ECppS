#ifndef ECPPS_SYSTEM_HPP
#define ECPPS_SYSTEM_HPP

#include <sol/table.hpp>
#include <SystemDef.hpp>

class System
{
public:
    System(const SystemDef&);
    const SystemDef& def() const;
private:
    friend class ConcurrentStep;
    friend class LinearStep;
    sol::table m_properties;
    sol::function m_process;
    const SystemDef& m_def;
};

#endif //ECPPS_SYSTEM_HPP
