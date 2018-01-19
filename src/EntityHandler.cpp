#include <EntityHandler.hpp>
#include <Component.hpp>
#include <ComponentDef.hpp>
#include <EntityStorage.hpp>

EntityHandler::EntityHandler() :
        m_ID(0),
        m_storage(nullptr)
{

}


EntityHandler::EntityHandler(EntityID id, EntityStorage* storage) :
    m_ID(id),
    m_storage(storage)
{

}

bool EntityHandler::hasComponent(const ComponentDef& def)
{
    if(m_storage && m_ID != 0)
    {
        auto& components = getComponents();
        return components.find(def) != std::end(components);
    }
    return false;
}

Component& EntityHandler::addComponent(const ComponentDef& def)
{
    if(m_storage && m_ID != 0)
    {
        auto& components = getComponents();
        if(components.find(def) == std::end(components))
        {
            auto &component = components[def] = def.create();
            return component;
        }
        else
            throw std::runtime_error("Trying to add component which already exists");
    }
    throw std::runtime_error("Trying to add component to invalid entity");
}

const EntityID& EntityHandler::id() const
{
    return m_ID;
}

Component& EntityHandler::getComponent(const ComponentDef &def)
{
    if(m_storage && m_ID != 0)
    {
        if(hasComponent(def))
            return getComponents()[def];
        throw std::runtime_error("Entity doesn't have " + def.name() + " component");
    }
    throw std::runtime_error("Trying to get component from invalid entity");
    
}

Components& EntityHandler::getComponents()
{
    return m_storage->getComponents(m_ID);
}
