cmake_minimum_required(VERSION 3.0)

set(EVENTS_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/EventDispatcher.cpp
)

add_library(events SHARED ${EVENTS_SRC})

