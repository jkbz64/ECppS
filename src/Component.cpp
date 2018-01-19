#include <Component.hpp>

sol::object Component::getVariable(const std::string& name)
{
    if(m_valid)
    {
        auto found = m_data.find(name);
        if(found != m_data.end())
        {
            auto value = found->second;
            if(value.get_type() == sol::type::lightuserdata)
                throw std::runtime_error("Error __index: Trying to index " + name + " which is nil in " + m_name);
            return value;
        }
        else
            throw std::runtime_error("Error __index: " + name + " doesn't exists in " + m_name);
    }
    else
        throw std::runtime_error("Error: trying to index invalid Component");
}

void Component::setVariable(const std::string& name, sol::object object)
{
    if(m_valid && !m_readonly)
    {
        auto found = m_data.find(name);
        if(found != std::end(m_data))
            m_data[name] = object;
        else
            throw std::runtime_error("Error __newindex: " + name + " doesn't exists in " + m_name);
    }
    else
        throw std::runtime_error("Error: trying to new_index invalid/readonly Component");
}
