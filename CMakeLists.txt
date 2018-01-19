cmake_minimum_required(VERSION 3.1)
project(ECppS)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build(Release or Debug)" FORCE)
endif()

# Enforce C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wpedantic -pedantic -pedantic-errors -g")
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

file(GLOB_RECURSE HDRS include/*.hpp)
file(GLOB_RECURSE SRCS src/*.cpp)

add_library(ECppS SHARED ${HDRS} ${SRCS})

target_include_directories(ECppS PUBLIC
				${CMAKE_SOURCE_DIR}/include/
				${LUA53_INCLUDE_DIR}
				${CMAKE_SOURCE_DIR}/lib/sol2/
)

target_link_libraries(ECppS ${LUA53_LIBRARIES})
