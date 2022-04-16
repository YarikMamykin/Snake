cmake_minimum_required(VERSION 3.0)

add_executable(SynchronousCommandsTest
  ${CMAKE_CURRENT_SOURCE_DIR}/SynchronousCommandsTest.cpp
  ${CMAKE_SOURCE_DIR}/src/commands/synchronous_commands/QueryTextHeight/QueryTextHeight.cpp
  ${CMAKE_SOURCE_DIR}/src/commands/synchronous_commands/QueryTextWidth/QueryTextWidth.cpp
  ${CMAKE_SOURCE_DIR}/src/commands/synchronous_commands/QueryWindowFrame/QueryWindowFrame.cpp
)
add_dependencies(SynchronousCommandsTest test_xproxy)
target_link_libraries(SynchronousCommandsTest
  gtest
  gtest_main
  gmock
  test_xproxy
  color
  query_lock
  settings
)
add_test(NAME SynchronousCommandsTest COMMAND SynchronousCommandsTest)
