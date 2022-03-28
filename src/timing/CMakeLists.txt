cmake_minimum_required(VERSION 3.0)

set(TIMER_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/Timer.cpp
)

add_library(timer SHARED ${TIMER_SRC})
