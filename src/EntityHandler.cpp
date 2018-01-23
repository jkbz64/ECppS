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
        return m_storage->hasComponent(m_ID, def);
    return false;
}

Component& EntityHandler::addComponent(const ComponentDef& def)
{
    if(m_storage && m_ID != 0)
        return m_storage->createComponent(m_ID, def);
    throw std::runtime_error("Trying to add component to invalid entity");
}

const EntityID& EntityHandler::id() const
{
    return m_ID;
}

Component& EntityHandler::getComponent(const ComponentDef &def)
{
    if(m_storage && m_ID != 0)
        return m_storage->getComponent(m_ID, def);
    throw std::runtime_error("Trying to get component from invalid entity");
    
}
