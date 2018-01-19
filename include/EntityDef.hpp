#ifndef ECPPS_ENTITYDEF_HPP
#define ECPPS_ENTITYDEF_HPP

#include <sol/function.hpp>
#include <EntityHandler.hpp>
#include <ComponentDef.hpp>

class EntityHandler;

class EntityDef
{
public:
    EntityDef() = default;
    ~EntityDef() = default;
    
    EntityDef& component(ComponentDef&);
    EntityDef& component(ComponentDef&, sol::function);
    
    EntityDef& done();
    EntityDef& done(sol::function);
private:
    friend class ECppS;
    friend class EntityStorage;
    
    std::vector<std::function<void(EntityHandler&)>> m_components;
    std::function<void(EntityHandler&, sol::variadic_args)> m_done;
    
};

#endif //ECPPS_ENTITYDEF_HPP
