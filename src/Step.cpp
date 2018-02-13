#include <Step.hpp>
#include <sol/variadic_args.hpp>
#include <Context.hpp>
#include <iostream>

namespace
{
    using VisitedDefs = std::map<SystemDef, bool, SystemDef::Less>;
    
    void topologicSort(const SystemDef& def, VisitedDefs& visited, SystemChain& chain)
    {
        visited[def] = true;
        
        for(const auto& adj : def.dependencies())
        {
            if(!visited[adj])
                topologicSort(adj, visited, chain);
        }
        chain.emplace_back(def);
    }
    
    void count(VisitedDefs& visited, const SystemDef& root)
    {
        for(auto& dep : root.dependencies())
            count(visited, dep);
        visited.emplace(root, false);
    }
}

Step::Step() = default;
Step::~Step() = default;

bool Step::updateCache(const SystemDef &def)
{
    if(m_context->hasSystem(def))
    {
        if(m_cachedChains.find(def) == std::end(m_cachedChains))
        {
            //Stack
            auto& cachedChain = m_cachedChains[def];
            if(!cachedChain.empty())
                cachedChain.clear();
            
            // Get number of vertices in graph
            VisitedDefs visited;
            count(visited, def);
            
            for(const auto& visitedPair : visited)
            {
                if(!visitedPair.second)
                    topologicSort(visitedPair.first, visited, cachedChain);
            }
            return true;
        }
    }
    return false;
}

