#ifndef ECPPS_COMPONENT_HPP
#define ECPPS_COMPONENT_HPP

#include <cstddef>
#include <unordered_map>
#include <sol/state_view.hpp>

using ComponentData = std::unordered_map<std::string, sol::object>;

class Component
{
public:
    Component() = default;
    Component(std::string name) : m_name(std::move(name)) { }
    ~Component() = default;
    
    sol::object getVariable(const std::string&);
    void setVariable(const std::string&, sol::object);
private:
    bool m_valid{false};
    bool m_readonly{false};
    friend class ECppS;
    friend class ComponentDef;
    std::string m_name;
    ComponentData m_data;
};

#endif //ECPPS_COMPONENT_HPP
