#include <EntityStorage.hpp>
#include <EntityDef.hpp>
#include <ComponentDef.hpp>
#include <iostream>

EntityHandler EntityStorage::createEntity()
{
    const auto id = m_nextID++;
    m_entities.emplace(id);
    return EntityHandler{id, this};
}

EntityHandler EntityStorage::createEntity(EntityDef &def)
{
    const auto id = m_nextID++;
    m_entities.emplace(id);
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
    m_entities.emplace(id);
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
        return {id, this};
    throw std::runtime_error("There's no entity with ID: " + id);
}

Component& EntityStorage::createComponent(EntityID id, const ComponentDef &def)
{
    if(m_components.find(def) == std::end(m_components))
        m_components[def] = std::map<EntityID, Component>();
    auto& components = m_components[def];
    auto where = components.find(id);
    if(where == std::end(components))
        where = components.emplace(id, def).first;
    return (*where).second;
}

Component& EntityStorage::getComponent(EntityID id, const ComponentDef& def)
{
    if(m_components.find(def) == std::end(m_components))
        throw std::runtime_error("Entity doesn't have " + def.name() + " component");
    auto& components = m_components[def];
    auto where = components.find(id);
    if(where != std::end(components))
        return (*where).second;
    throw std::runtime_error("Entity doesn't have this component");
}

bool EntityStorage::hasComponent(EntityID id, const ComponentDef &def)
{
    if(m_components.find(def) == std::end(m_components))
        return false;
    auto& components = m_components[def];
    return components.find(id) != std::end(components);
}