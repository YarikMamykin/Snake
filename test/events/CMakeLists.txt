cmake_minimum_required(VERSION 3.0)

add_executable(EventsTest
  ClientMessageEventTest.cpp
  ExposeEventTest.cpp
  KeyPressEventTest.cpp
  MouseButtonPressEventTest.cpp
  MouseMotionEventTest.cpp
)
target_link_libraries(EventsTest
  gtest
  gtest_main
  gmock
  events
)
add_test(NAME EventsTest COMMAND EventsTest)
