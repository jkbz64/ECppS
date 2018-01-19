#include <EntityStorage.hpp>
#include <EntityDef.hpp>
#include <ComponentDef.hpp>
#include <iostream>

Components& EntityStorage::getComponents(const EntityID& id)
{
    if(isValid(id))
        return m_entities[id];
    throw std::runtime_error("Error: trying to get components from invalid entity");
}

EntityHandler EntityStorage::createEntity()
{
    const auto id = m_nextID++;
    m_entities.emplace(id, Components());
    return EntityHandler{id, this};
}

EntityHandler EntityStorage::createEntity(EntityDef &def)
{
    const auto id = m_nextID++;
    m_entities.emplace(id, Components());
    auto handler = EntityHandler(id, this);
    for(auto& component : def.m_components)
        component(handler);
    sol::variadic_args args(nullptr);
    def.m_done(handler, args);
    return handler;
}

EntityHandler EntityStorage::createEntity(EntityDef &def, sol::variadic_args args)
{
    const auto id = m_nextID++;
    m_entities.emplace(id, Components());
    auto handler = EntityHandler(id, this);
    for(auto& component : def.m_components)
        component(handler);
    def.m_done(handler, args);
    return handler;
}

bool EntityStorage::isValid(const EntityID& id)
{
    return m_entities.find(id) != std::end(m_entities);
}

EntityHandler EntityStorage::getEntity(const EntityID& id)
{
    if(isValid(id))
    return EntityHandler();
}
