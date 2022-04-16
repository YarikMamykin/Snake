cmake_minimum_required(VERSION 3.0)

add_executable(ChangeViewTest
  ${CMAKE_CURRENT_SOURCE_DIR}/ChangeViewTest.cpp
)
target_link_libraries(ChangeViewTest
  gtest
  gtest_main
  gmock
  command_change_view
)
add_test(NAME ChangeViewTest COMMAND ChangeViewTest)
