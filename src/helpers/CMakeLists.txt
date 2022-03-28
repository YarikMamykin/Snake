cmake_minimum_required(VERSION 3.0)

set(HELPERS_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/Helper.cpp
)

add_library(helpers SHARED ${HELPERS_SRC})
