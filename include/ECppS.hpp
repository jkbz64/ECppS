#ifndef ECppS_HPP
#define ECppS_HPP
#include <sol/forward.hpp>

struct ECppS
{
    static sol::table createModule(sol::this_state);
};

extern "C"
{
    struct lua_State;
}

extern "C" int luaopen_ECppS(lua_State*);

#endif
