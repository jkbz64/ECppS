#include <Step.hpp>
#include <sol/variadic_args.hpp>
#include <Context.hpp>
#include <iostream>

namespace
{
    static std::unordered_map<SystemDef, std::vector<SystemDef>, SystemDef::Hasher, SystemDef::Comparator> cachedChains;
    void addNextSystem(SystemChain& chain, const SystemDef& root)
    {
        bool allDeps = true;
        for(const auto& dep : root.dependencies())
        {
            if(std::find_if(chain.begin(), chain.end(), [&dep](const SystemDef& def)
            {
                return def.id() == dep.id();
            }) == std::end(chain))
            {
                allDeps = false;
                break;
            }
        }
        if(!allDeps)
        {
            for(const auto& dep : root.dependencies())
                addNextSystem(chain, dep);
        }
        else
        {
            if(std::find_if(chain.begin(), chain.end(), [&root](const SystemDef& def)
            {
                return def.id() == root.id();
            }) == std::end(chain))
                chain.emplace_back(root);
        }
    }
    
    void count(std::set<SystemDef, SystemDef::Less>& set, const SystemDef& root)
    {
        for(auto& dep : root.dependencies())
            count(set, dep);
        set.emplace(root);
    }
}

Step::Step(AbstractQueue* queue) :
    m_queue(queue)
{

}

Step::~Step()
{
    cachedChains.clear();
}

void Step::process(const SystemDef &def)
{
    if(m_context->hasSystem(def))
    {
        if(cachedChains.find(def) == std::end(cachedChains))
        {
            std::set<SystemDef, SystemDef::Less> countSet;
            count(countSet, def);
            std::size_t oldCount = m_chain.size();
            while(m_chain.size() < countSet.size() + oldCount)
            {
                addNextSystem(m_chain, def);
            }
            std::vector<SystemDef> defChain = {};
            for(auto i = oldCount; i < m_chain.size() - 1; ++i)
            {
                std::cerr << m_chain[i].id() << " ";
                defChain.emplace_back(m_chain[i]);
            }
            cachedChains.emplace(def, std::move(defChain));
        }
        else
        {
            for(const auto& chainElement : cachedChains[def])
            {
                m_chain.emplace_back(chainElement);
            }
        }
    }
}

