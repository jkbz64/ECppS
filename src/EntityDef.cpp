#include <EntityDef.hpp>

EntityDef& EntityDef::component(ComponentDef& def)
{
    if(m_done)
        return *this;
    
    m_components.emplace_back([def](EntityHandler& handler)
                              {
                                  handler.addComponent(def);
                              });
    return *this;
}

EntityDef& EntityDef::component(ComponentDef& def, sol::function f)
{
    if(m_done)
        return *this;
    
    m_components.emplace_back([def, f = std::move(f)](EntityHandler& handler)
                              {
                                  handler.addComponent(def);
                              });
    return *this;
}

EntityDef& EntityDef::done()
{
    if(m_done)
        return *this;
    m_done = [](EntityHandler&, sol::variadic_args){};
    return *this;
}

EntityDef& EntityDef::done(sol::function done)
{
    if(m_done)
        return *this;
    m_done = std::move(done);
    return *this;
}