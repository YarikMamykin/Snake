cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_COMPILER /usr/bin/g++-10)
set(CMAKE_C_COMPILER /usr/bin/gcc-10)
set(CMAKE_CXX_FLAGS "-g -fPIC -rdynamic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Snake)

include("${CMAKE_CURRENT_SOURCE_DIR}/External.cmake")

include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(src)

if(${UNIT_TESTS})
  add_subdirectory(test)
endif()
