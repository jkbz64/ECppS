#ifndef ECPPS_SYSTEMDEF_HPP
#define ECPPS_SYSTEMDEF_HPP

#include <cstddef>
#include <set>
#include <sol/function.hpp>

class System;
class ComponentDef;

class SystemDef
{
public:
    struct Hasher
    {
        std::size_t operator()(const SystemDef&) const;
    };
    
    struct Comparator
    {
        bool operator()(const SystemDef&, const SystemDef&) const noexcept;
    };
    
    SystemDef();
    ~SystemDef() = default;
    
    const std::size_t& id() const;
    
    SystemDef& init(sol::function);
    SystemDef& read(const ComponentDef&);
    SystemDef& write(const ComponentDef&);
    SystemDef& depends(const SystemDef&);
    SystemDef& process(sol::function);
private:
    std::size_t m_ID;
    std::function<void(System&, sol::variadic_args)> m_init;
    std::set<std::size_t> m_dependencies;
    std::set<std::size_t> m_reads;
    std::set<std::size_t> m_writes;
};

#endif //ECPPS_SYSTEMDEF_HPP
