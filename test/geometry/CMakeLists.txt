cmake_minimum_required(VERSION 3.0)

add_executable(RectangleTest
  RectangleTest.cpp
)
target_link_libraries(RectangleTest
  gtest
  gtest_main
)
add_test(NAME RectangleTest COMMAND RectangleTest)

add_executable(PointTest
  PointTest.cpp
)
target_link_libraries(PointTest
  gtest
  gtest_main
)
add_test(NAME PointTest COMMAND PointTest)
