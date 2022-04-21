cmake_minimum_required(VERSION 3.0)

include("${CMAKE_CURRENT_SOURCE_DIR}/Base.cmake")

project(Snake)

include("${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}.cmake")

include("${CMAKE_CURRENT_SOURCE_DIR}/External.cmake")

include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(src)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  add_subdirectory(test)
endif()
