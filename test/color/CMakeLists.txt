cmake_minimum_required(VERSION 3.0)

add_executable(ColorTest
  ColorTest.cpp
)
target_link_libraries(ColorTest
  gtest
  gtest_main
  color
)
add_test(NAME ColorTest COMMAND ColorTest)

add_executable(ColorPalleteTest
  ColorPalleteTest.cpp
)
target_link_libraries(ColorPalleteTest
  gtest
  gtest_main
  color
)
add_test(NAME ColorPalleteTest COMMAND ColorPalleteTest)

