cmake_minimum_required(VERSION 3.0)

add_executable(GraphicsCommandsTest
  ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsCommandsTest.cpp
  ${CMAKE_SOURCE_DIR}/src/commands/graphics_commands/DrawRectangle/DrawRectangle.cpp
  ${CMAKE_SOURCE_DIR}/src/commands/graphics_commands/DrawCircle/DrawCircle.cpp
  ${CMAKE_SOURCE_DIR}/src/commands/graphics_commands/FillRectangle/FillRectangle.cpp
  ${CMAKE_SOURCE_DIR}/src/commands/graphics_commands/FillCircle/FillCircle.cpp
  ${CMAKE_SOURCE_DIR}/src/commands/graphics_commands/DrawText/DrawText.cpp
)
add_dependencies(GraphicsCommandsTest test_xproxy)
target_link_libraries(GraphicsCommandsTest
  gtest
  gtest_main
  gmock
  test_xproxy
  color
)
add_test(NAME GraphicsCommandsTest COMMAND GraphicsCommandsTest)
