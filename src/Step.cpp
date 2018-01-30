#include <Step.hpp>
#include <sol/variadic_args.hpp>
#include <Context.hpp>

namespace
{
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

Step::~Step() = default;

void Step::process(const SystemDef &def)
{
    if(m_context->hasSystem(def))
    {
        std::set<SystemDef, SystemDef::Less> countSet;
        count(countSet, def);
        std::size_t oldCount = m_chain.size();
        while(m_chain.size() < countSet.size() + oldCount)
        {
            addNextSystem(m_chain, def);
        }
    }
}

