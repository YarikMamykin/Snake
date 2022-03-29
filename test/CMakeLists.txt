cmake_minimum_required(VERSION 3.0)

include("${CMAKE_CURRENT_SOURCE_DIR}/Gtest.cmake")

add_subdirectory(abstractions)
add_subdirectory(color)
add_subdirectory(geometry)
add_subdirectory(timing)
add_subdirectory(events)
add_subdirectory(views)
