cmake_minimum_required(VERSION 3.0)

add_executable(ExitApplicationTest
  ${CMAKE_CURRENT_SOURCE_DIR}/ExitApplicationTest.cpp
)
target_link_libraries(ExitApplicationTest
  gtest
  gtest_main
  gmock
  command_exit_application
)
add_test(NAME ExitApplicationTest COMMAND ExitApplicationTest)
