cmake_minimum_required(VERSION 3.0)

add_executable(QueryLockTest
  ${CMAKE_CURRENT_SOURCE_DIR}/QueryLockTest.cpp
)
target_link_libraries(QueryLockTest
  gtest
  gtest_main
  gmock
  query_lock
)
add_test(NAME QueryLockTest COMMAND QueryLockTest)
