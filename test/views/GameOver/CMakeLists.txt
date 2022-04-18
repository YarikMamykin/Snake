cmake_minimum_required(VERSION 3.0)

add_executable(GameOverTests
  ${CMAKE_CURRENT_SOURCE_DIR}/GameOverTests.cpp
  ${CMAKE_SOURCE_DIR}/src/views/GameOver/GameOver.cpp
)
target_include_directories(GameOverTests
  BEFORE PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(GameOverTests
  gtest
  gtest_main
  gmock
  color
  anchor_handlers
  command_change_view
  settings
)
add_test(NAME GameOverTests COMMAND GameOverTests)
