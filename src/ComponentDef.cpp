#include <ComponentDef.hpp>

ComponentDef::ComponentDef(sol::this_state L, std::string name) :
    m_lua(L),
    m_name(std::move(name)),
    m_ID(0)
{
    static std::size_t counter = 0;
    m_ID = counter++;
}

ComponentDef::~ComponentDef() = default;

ComponentDef& ComponentDef::var(const std::string& name)
{
    if(m_done)
        return *this;
    m_variables.emplace_back([L = m_lua.L, name](ComponentData& t)
                             {
                                 int nil = 0;
                                 t[name] = sol::make_object(L, sol::make_light(nil));
                             });
    return *this;
}

ComponentDef& ComponentDef::var(const std::string& name, double value)
{
    if(m_done)
        return *this;
    
    m_variables.emplace_back([L = m_lua.L, name, value](ComponentData& t)
                             {
                                 t[name] = sol::make_object(L, value);
                             });
    return *this;
}

ComponentDef& ComponentDef::var(const std::string& name, sol::function functor)
{
    if(m_done)
        return *this;
    
    m_variables.emplace_back([L = m_lua.L, name, functor](ComponentData& t)
                             {
                                 t[name] = functor;
                             });
    return *this;
}

ComponentDef& ComponentDef::var(const std::string& name, const std::string& string)
{
    if(m_done)
        return *this;
    
    m_variables.emplace_back([L = m_lua.L, name, string](ComponentData& t)
                             {
                                 t[name] = sol::make_object(L, string);
                             });
    return *this;
}

ComponentDef& ComponentDef::var(const std::string& name, sol::object obj)
{
    if(m_done)
        return *this;
    
    m_variables.emplace_back([name, obj](ComponentData& t)
                             {
                                 t[name] = obj;
                             });
    return *this;
}

ComponentDef& ComponentDef::var_f(const std::string& name, sol::function _new, sol::variadic_args args)
{
    if(m_done)
        return *this;
    
    if(_new.valid())
        m_variables.emplace_back([name, _new, args](ComponentData& t)
                                 {
                                     sol::object obj = _new.call(args);
                                     if(obj.valid())
                                         t[name] = obj;
                                     else
                                         throw std::runtime_error("Function doesn't return anything! Variable: " + name);
                                 });
    else
        throw std::runtime_error("New function not valid! Variable: " + name);
    return *this;
}

ComponentDef& ComponentDef::done(sol::this_state L)
{
    m_lua = L;
    if(m_done)
        return *this;
        
    m_done = [](Component&, sol::variadic_args){};
    return *this;
}


ComponentDef& ComponentDef::done(sol::this_state L, sol::function f)
{
    m_lua = L;
    if(m_done)
        return *this;
    
    m_done = std::move(f);
    return *this;
}

Component ComponentDef::create() const
{
    if(m_lua && m_done)
    {
        Component component(m_name);
        for(const auto &def : m_variables)
            def(component.m_data);
        component.m_valid = true;
        
        if(m_done)
            m_done(component, sol::variadic_args(m_lua));
        return component;
    }
    return Component();
}

const std::size_t& ComponentDef::id() const
{
    return m_ID;
}

const std::string& ComponentDef::name() const
{
    return m_name;
}

std::size_t ComponentDef::Hasher::operator()(const ComponentDef &def) const noexcept
{
    return def.m_ID;
}

bool ComponentDef::Comparator::operator()(const ComponentDef &a, const ComponentDef &b) const noexcept
{
    return a.m_ID == b.m_ID;
}
