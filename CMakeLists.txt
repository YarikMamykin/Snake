cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER /usr/bin/g++-10)
set(CMAKE_C_COMPILER /usr/bin/gcc-10)
set(CMAKE_CXX_FLAGS "-g -pthread -fPIC -rdynamic")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Snake)

find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})

add_subdirectory(src)
