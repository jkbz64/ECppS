#ifndef ECPPS_CONTEXT_HPP
#define ECPPS_CONTEXT_HPP

#include <queue>
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
private:
    EntityStorage m_storage;
    std::unordered_map<SystemDef, System, SystemDef::Hasher> m_systems;
    std::unique_ptr<Step> m_step;
};

#endif //ECPPS_CONTEXT_HPP
