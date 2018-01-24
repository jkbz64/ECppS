#ifndef ECPPS_TASK_HPP
#define ECPPS_TASK_HPP

#include <SystemDef.hpp>
#include <System.hpp>

using DoneSystems = std::map<SystemDef, std::atomic<bool>, SystemDef::Less>;

struct Task
{
    Task()
    {
        m_function = []{ return true; };
    }
    
    Task(System& system, std::reference_wrapper<DoneSystems> deps, sol::variadic_args args)
    {
        m_function = [&system, dependencies = deps, args]
        {
            auto& def = system.m_def;
            auto& doneSystems = dependencies.get();
            if(doneSystems[def].load())
                return true;
            
            for(auto& dependency : system.m_def.m_dependencies)
            {
                if(!doneSystems[dependency].load())
                    return false;
            }
            
            system.process(args);
            bool expected = false;
            while(doneSystems[system.m_def].compare_exchange_strong(expected, true))
                continue;
            return true;
        };
    }
    std::function<bool()> m_function;
};

#endif //ECPPS_TASK_HPP
