cmake_minimum_required(VERSION 3.0)

set(COLOR_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/Color.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ColorPallete.cpp
)

add_library(color SHARED ${COLOR_SRC})
