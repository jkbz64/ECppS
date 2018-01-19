#include <Step.hpp>
#include <sol/variadic_args.hpp>
#include <Context.hpp>
#include <System.hpp>

void Step::process(const SystemDef &def, sol::variadic_args args)
{
    m_actions.emplace_back([def, args](Context& context) -> SystemPair
                           {
                               std::reference_wrapper<System> ref = context.getSystem(def);
                               return std::make_tuple(ref, args);
                           });
}
