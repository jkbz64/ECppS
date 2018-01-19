#ifndef ECPPS_CONTEXT_HPP
#define ECPPS_CONTEXT_HPP

#include <SystemDef.hpp>
#include <System.hpp>
#include <EntityStorage.hpp>
#include <Step.hpp>

class Context
{
public:
    Context();
    ~Context();
    
    void addSystem(const SystemDef&);
    void removeSystem(const SystemDef&);
    System& getSystem(const SystemDef&);
    
    void step(sol::function);
private:
    EntityStorage m_storage;
    std::unordered_map<SystemDef, System, SystemDef::Hasher, SystemDef::Comparator> m_systems;
    std::unique_ptr<Step> m_step;
};

#endif //ECPPS_CONTEXT_HPP
