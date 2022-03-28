cmake_minimum_required(VERSION 3.0)

set(GAME_OBJECTS_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/Snake.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MovementController.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Food.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/FoodGenerator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Info.cpp
)

add_library(game_objects SHARED ${GAME_OBJECTS_SRC})
