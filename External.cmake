cmake_minimum_required(VERSION 3.0)

find_package(Threads REQUIRED)

find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})
