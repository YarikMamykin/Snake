cmake_minimum_required(VERSION 3.0)

add_library(view_game_menu OBJECT
  ${CMAKE_CURRENT_SOURCE_DIR}/GameMenu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Item.cpp
)

add_dependencies(view_game_menu x11_text_label)
target_link_libraries(view_game_menu x11_text_label)
