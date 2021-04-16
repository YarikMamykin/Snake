cmake_minimum_required(VERSION 3.0)

project(Snake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -pthread -fPIC -rdynamic")

find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})

add_subdirectory(src)
