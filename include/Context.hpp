#ifndef ECPPS_CONTEXT_HPP
#define ECPPS_CONTEXT_HPP

#include <SystemDef.hpp>
#include <System.hpp>
#include <EntityStorage.hpp>
#include <Step.hpp>

class Context
{
public:
    Context(sol::this_state);
    ~Context();
    
    void addSystem(const SystemDef&, sol::variadic_args);
    void removeSystem(const SystemDef&);
    System& getSystem(const SystemDef&);
    bool hasSystem(const SystemDef&);
    
    void setStep(std::unique_ptr<Step>&);
    
    void step(sol::function);
private:
    sol::this_state m_L;
    EntityStorage m_storage;
    std::unordered_map<SystemDef, System, SystemDef::Hasher, SystemDef::Comparator> m_systems;
    std::unique_ptr<Step> m_step;
};

#endif //ECPPS_CONTEXT_HPP
