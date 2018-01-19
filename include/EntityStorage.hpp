#ifndef ECPPS_ENTITYSTORAGE_HPP
#define ECPPS_ENTITYSTORAGE_HPP

#include <set>
#include <Component.hpp>
#include <EntityHandler.hpp>
#include <ComponentDef.hpp>

class EntityDef;

class EntityStorage
{
public:
    EntityStorage() = default;
    ~EntityStorage() = default;
    
    EntityHandler createEntity();
    EntityHandler createEntity(EntityDef&);
    EntityHandler createEntity(EntityDef&, sol::variadic_args);
    
    EntityHandler getEntity(const EntityID&);
    
    bool isValid(const EntityID&);
    Components& getComponents(const EntityID&);
private:
    EntityID m_nextID{1};
    std::unordered_map<EntityID, Components> m_entities;
};

#endif //ECPPS_ENTITYSTORAGE_HPP
