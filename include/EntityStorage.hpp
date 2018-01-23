#ifndef ECPPS_ENTITYSTORAGE_HPP
#define ECPPS_ENTITYSTORAGE_HPP

#include <Component.hpp>
#include <EntityHandler.hpp>
#include <ComponentDef.hpp>

class EntityStorage
{
public:
    EntityStorage() = default;
    ~EntityStorage() = default;
    
    EntityHandler createEntity();
    EntityHandler createEntity(EntityDef&);
    EntityHandler createEntity(EntityDef&, sol::variadic_args);
    
    EntityHandler getEntity(const EntityID&);
    Component& getComponent(EntityID, const ComponentDef&);
    bool hasComponent(EntityID, const ComponentDef&);
    
    bool isValid(const EntityID&);
private:
    EntityID m_nextID{1};
    std::unordered_set<EntityID> m_entities;
    std::unordered_map<ComponentDef, std::map<EntityID, Component>, ComponentDef::Hasher, ComponentDef::Comparator> m_components;
    friend class EntityHandler;
    Component& createComponent(EntityID, const ComponentDef&);
};

#endif //ECPPS_ENTITYSTORAGE_HPP
