#ifndef ECPPS_ENTITYHANDLER_HPP
#define ECPPS_ENTITYHANDLER_HPP

#include <string>
#include <unordered_map>
#include "ComponentDef.hpp"

class Component;
class ComponentDef;
class EntityStorage;

using EntityID = std::size_t;
using ComponentID = std::size_t;
using Components = std::unordered_map<ComponentDef, Component, ComponentDef::Hasher, ComponentDef::Comparator>;

class EntityHandler
{
public:
    EntityHandler();
    EntityHandler(EntityID, EntityStorage*);
    const EntityID& id() const;
    bool hasComponent(const ComponentDef&);
    Component& addComponent(const ComponentDef&);
    Component& getComponent(const ComponentDef&);
private:
    friend class ECppS;
    EntityID m_ID{0};
    EntityStorage *m_storage;
    
    Components& getComponents();
};

#endif
