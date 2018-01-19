#include <LinearStep.hpp>
#include <System.hpp>

void LinearStep::run(Context& context)
{
    for(auto& actionCallable : m_actions)
    {
        auto&& action = actionCallable(context);
        System& system = std::get<0>(action).get();
        sol::variadic_args args = std::get<1>(action);
    }
}

