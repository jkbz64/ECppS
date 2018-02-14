#include <LinearStep/LinearStep.hpp>
#include <Context.hpp>

LinearStep::LinearStep()
{

}

void LinearStep::process(const SystemDef &def)
{
    updateCache(def);
    for(auto& system : m_cachedChains[def])
        system.m_process.call();
}
