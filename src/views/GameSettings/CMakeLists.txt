cmake_minimum_required(VERSION 3.0)

add_library(view_game_settings OBJECT
  ${CMAKE_CURRENT_SOURCE_DIR}/GameSettings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Setting.cpp
)
