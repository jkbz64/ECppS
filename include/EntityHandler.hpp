#ifndef ECPPS_ENTITYHANDLER_HPP
#define ECPPS_ENTITYHANDLER_HPP

#include <string>
#include <unordered_map>
#include <ComponentDef.hpp>
#include <fwd.hpp>

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
};

#endif
