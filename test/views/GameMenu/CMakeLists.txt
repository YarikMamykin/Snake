cmake_minimum_required(VERSION 3.0)

add_executable(GameMenuTests
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GameMenuTests.cpp
  ${CMAKE_SOURCE_DIR}/src/views/GameMenu/GameMenu.cpp
  ${CMAKE_SOURCE_DIR}/src/views/GameMenu/Item.cpp
)
target_include_directories(GameMenuTests
  BEFORE PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(GameMenuTests
  gtest
  gtest_main
  gmock
  color
  anchor_handlers
  command_change_view
  command_exit_application
  settings
)
add_test(NAME GameMenuTests COMMAND GameMenuTests)
