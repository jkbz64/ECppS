#ifndef ECPPS_COMPONENT_HPP
#define ECPPS_COMPONENT_HPP

#include <unordered_map>
#include <sol/state_view.hpp>
#include <mutex>

using ComponentData = std::unordered_map<std::string, sol::object>;
class ComponentDef;

class Component
{
public:
    Component(const ComponentDef&);
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
