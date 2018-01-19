#include <ECppS.hpp>
#include <sol/state_view.hpp>
#include <EntityHandler.hpp>
#include <ComponentDef.hpp>
#include <EntityDef.hpp>
#include <EntityStorage.hpp>
#include <SystemDef.hpp>
#include <System.hpp>
#include <Context.hpp>

namespace
{
    template<class T>
    struct functor_info;
    
    template<class R, class Arg, class T>   // Strip argument type to non-const, non-reference
    struct functor_info<R (T::*)(Arg)> { using return_type = R;
                                         using member_type = T;
                                         using argument_type = std::remove_const_t        <
                                                               std::remove_reference_t    <
                                                                        Arg                >>;
                                         
    };
    
}

namespace sol
{
    template<typename F,
             typename R = typename functor_info<F>::return_type,
             typename T = typename functor_info<F>::member_type,
             typename Arg = typename functor_info<F>::argument_type,
             typename std::enable_if_t<std::is_same<R, void>::value>
             >
    constexpr auto sizeSetter(F f)
    {
        static_assert(std::is_same<Arg, std::size_t>::value, " func should take size_t as parameter");
        return [f](T& t, int val)
        {
            (t.*f)(val);
        };
    }
    
    template<typename F,
            typename R = typename functor_info<F>::return_type,
            typename T = typename functor_info<F>::member_type,
            typename Arg = typename functor_info<F>::argument_type,
            typename = std::enable_if_t<!std::is_same<R, void>::value>,
            typename = void>
    constexpr auto sizeSetter(F f)
    {
        static_assert(std::is_same<Arg, std::size_t>::value, " func should take size_t as parameter");
        return [f](T& t, int val)
        {
            return (t.*f)(val);
        };
    }
}

sol::table ECppS::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    
    module.new_usertype<ComponentDef>("ComponentDef",
                                      "new", sol::no_constructor,
                                      "var",
                                      sol::overload(
                                              static_cast<ComponentDef&(ComponentDef::*)(const std::string&)>(&ComponentDef::var),
                                              static_cast<ComponentDef&(ComponentDef::*)(const std::string&, double)>(&ComponentDef::var),
                                              static_cast<ComponentDef&(ComponentDef::*)(const std::string&, const std::string&)>(&ComponentDef::var),
                                              static_cast<ComponentDef&(ComponentDef::*)(const std::string&, sol::function)>(&ComponentDef::var),
                                              static_cast<ComponentDef&(ComponentDef::*)(const std::string&, sol::object)>(&ComponentDef::var)
                                      ),
                                      "var_f", &ComponentDef::var_f,
                                      "done",
                                      sol::overload(
                                              static_cast<ComponentDef&(ComponentDef::*)(sol::this_state)>(&ComponentDef::done),
                                              static_cast<ComponentDef&(ComponentDef::*)(sol::this_state, sol::function)>(&ComponentDef::done)
                                      )
    );
    
    module.new_usertype<Component>("Component",
                                   "new", sol::no_constructor,
                                   sol::meta_function::index, &Component::getVariable,
                                   sol::meta_function::new_index, &Component::setVariable
    );
    
    std::unordered_map<std::string, ComponentDef>& components = module["registeredComponents"] = std::unordered_map<std::string, ComponentDef>();
    std::unordered_map<std::string, EntityDef>& entities = module["registeredEntities"] = std::unordered_map<std::string, EntityDef>();
    std::unordered_map<std::string, SystemDef>& systems = module["registeredSystems"] = std::unordered_map<std::string, SystemDef>();
    
    module.set_function("makeComponentDef", [&components](sol::this_state L, const std::string& name) -> ComponentDef&
    {
        if(components.find(name) == std::end(components))
            components.emplace(std::piecewise_construct,
                               std::forward_as_tuple(name),
                               std::forward_as_tuple(L, name));
        return components.at(name);
    });
    
    module.set_function("makeEntityDef", [&entities](const std::string& name) -> EntityDef&
    {
        if(entities.find(name) == std::end(entities))
            entities.emplace(std::piecewise_construct,
                               std::forward_as_tuple(name),
                               std::forward_as_tuple());
        return entities.at(name);
    });
    
    module.set_function("makeSystemDef", [&systems](const std::string& name) -> SystemDef&
    {
        if(systems.find(name) == std::end(systems))
            systems.emplace(std::piecewise_construct,
                               std::forward_as_tuple(name),
                               std::forward_as_tuple());
        return systems.at(name);
    });
    
    module.new_usertype<EntityDef>("EntityDef",
                                   "component",
                                   sol::overload(
                                           static_cast<EntityDef&(EntityDef::*)(ComponentDef&)>(&EntityDef::component),
                                           static_cast<EntityDef&(EntityDef::*)(ComponentDef&, sol::function)>(&EntityDef::component)
                                   ),
                                   "done",
                                   sol::overload(
                                           static_cast<EntityDef&(EntityDef::*)()>(&EntityDef::done),
                                           static_cast<EntityDef&(EntityDef::*)(sol::function)>(&EntityDef::done)
                                   )
    );
    
    module.new_usertype<EntityHandler>("Entity",
                                       "new", sol::no_constructor,
                                       "ID", sol::property([](EntityHandler& e) { return static_cast<int>(e.id()); }),
                                       "hasComponent", &EntityHandler::hasComponent,
                                       "addComponent", &EntityHandler::addComponent,
                                       sol::meta_function::index, &EntityHandler::getComponent
    );
    
    module.new_usertype<EntityStorage>("EntityStorage",
                                       "new", sol::constructors<EntityStorage()>(),
                                       "createEntity",
                                       sol::overload(
                                               static_cast<EntityHandler(EntityStorage::*)()>(&EntityStorage::createEntity),
                                               static_cast<EntityHandler(EntityStorage::*)(EntityDef&)>(&EntityStorage::createEntity),
                                               static_cast<EntityHandler(EntityStorage::*)(EntityDef&, sol::variadic_args)>(&EntityStorage::createEntity)
                                       ),
                                       "getEntity", sol::sizeSetter(&EntityStorage::getEntity)
    );
    
    module.new_usertype<SystemDef>("SystemDef",
                                   "init", &SystemDef::init,
                                   "read", &SystemDef::read,
                                   "write", &SystemDef::write,
                                   "depends", &SystemDef::depends
    );
    
    module.new_usertype<System>("System",
                                "new", sol::no_constructor
                                //"addDependency", &System::addDependency,
    );
    
    module.new_usertype<Context>("Context",
                                 "new", sol::constructors<Context()>(),
                                 "addSystem", &Context::addSystem,
                                 "removeSystem", &Context::removeSystem,
                                 "getSystem", &Context::getSystem
    );
    
    module.new_usertype<Step>("Step",
                              "new", sol::no_constructor,
                              "process", &Step::process
    );
    return module;
}

extern "C" int luaopen_ECppS(lua_State* L)
{
    return sol::stack::call_lua(L, 1, ECppS::createModule);
}