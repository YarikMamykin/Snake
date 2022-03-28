cmake_minimum_required(VERSION 3.0)

add_executable(RestrictedValueTest
  RestrictedValueTest.cpp
)
target_link_libraries(RestrictedValueTest
  gtest
  gtest_main
)
add_test(NAME RestrictedValueTest COMMAND RestrictedValueTest)

