cmake_minimum_required(VERSION 3.0)

add_executable(GameAboutTests
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GameAboutTests.cpp
)

target_link_libraries(GameAboutTests
  gtest
  gtest_main
  gmock
  view_game_about
  x11_text_label
  anchor_handlers
  color
  command_fill_rectangle
  command_draw_rectangle
  command_draw_text
  command_query_text_width
  command_query_text_height
  command_change_view
  graphics_commands
  synchronous_commands
  settings
  query_lock
  xproxy
  helpers
)

add_test(NAME GameAboutTests COMMAND GameAboutTests)
