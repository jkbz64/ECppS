#ifndef ECPPS_SYSTEMDEF_HPP
#define ECPPS_SYSTEMDEF_HPP

#include <cstddef>
#include <sol/function.hpp>
#include <fwd.hpp>


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
    
    struct Less
    {
        bool operator()(const SystemDef&, const SystemDef&) const noexcept;
    };
    
    using Dependencies = std::set<SystemDef, SystemDef::Less>;
    
    SystemDef();
    ~SystemDef() = default;
    
    const std::size_t& id() const;
    const Dependencies& dependencies() const;
    
    SystemDef& init(sol::function);
    SystemDef& read(const ComponentDef&);
    SystemDef& write(const ComponentDef&);
    SystemDef& depends(const SystemDef&);
    SystemDef& process(sol::function);
private:
    friend class Context;
    friend class Step;
    friend class System;
    std::size_t m_ID;
    std::function<void(System&, sol::variadic_args)> m_init;
    std::function<void()> m_process;
    Dependencies m_dependencies;
    
    std::set<std::size_t> m_reads;
    std::set<std::size_t> m_writes;
};

#endif //ECPPS_SYSTEMDEF_HPP
