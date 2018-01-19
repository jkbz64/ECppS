#ifndef ECPPS_COMPONENTDEF_HPP
#define ECPPS_COMPONENTDEF_HPP

#include <string>
#include <Component.hpp>

class ComponentDef
{
public:
    struct Hasher
    {
        std::size_t operator()(const ComponentDef&) const noexcept;
    };
    
    struct Comparator
    {
        bool operator()(const ComponentDef&, const ComponentDef&) const noexcept;
    };
    
    ComponentDef(sol::this_state, std::string);
    ~ComponentDef();
    
    bool operator==(const ComponentDef&);
    
    const std::size_t& id() const;
    const std::string& name() const;
    
    ComponentDef& var(const std::string&);
    ComponentDef& var(const std::string&, double);
    ComponentDef& var(const std::string&, sol::function);
    ComponentDef& var(const std::string&, const std::string&);
    ComponentDef& var(const std::string&, sol::object);
    ComponentDef& var_f(const std::string&, sol::function, sol::variadic_args);
    ComponentDef& done(sol::this_state);
    ComponentDef& done(sol::this_state, sol::function f);
    
    Component create() const;
private:
    friend class ECppS;
    sol::this_state m_lua;
    std::string m_name;
    std::size_t m_ID;
    std::vector<std::function<void(ComponentData&)>> m_variables;
    std::function<void(Component&, sol::variadic_args)> m_done;
};

#endif //ECPPS_COMPONENTDEF_HPP
