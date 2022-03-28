cmake_minimum_required(VERSION 3.0)

add_executable(TimerTest
  TimerTest.cpp
)
target_link_libraries(TimerTest
  gtest
  gtest_main
  timer
)
add_test(NAME TimerTest COMMAND TimerTest)
