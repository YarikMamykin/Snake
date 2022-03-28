cmake_minimum_required(VERSION 3.0)

set(GAME_VIEW_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/GameMenu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GameAction.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GameAbout.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GameOver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GameSettings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GameNone.cpp
)

add_library(game_views SHARED ${GAME_VIEW_SRC})
