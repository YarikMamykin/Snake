cmake_minimum_required(VERSION 3.0)

set(SETTINGS_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/Settings.cpp
)

add_library(settings SHARED ${SETTINGS_SRC})
