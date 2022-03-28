################################
# GTest
################################
add_subdirectory (${CMAKE_SOURCE_DIR}/googletest build)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src/include)

################################
# Unit Tests
################################
add_executable(TimerTest
  TimerTest.cpp
)
target_link_libraries(TimerTest
  gtest
  gtest_main
  timer
)
add_test(NAME TimerTest COMMAND TimerTest)

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

add_executable(RestrictedValueTest
  RestrictedValueTest.cpp
)
target_link_libraries(RestrictedValueTest
  gtest
  gtest_main
)
add_test(NAME RestrictedValueTest COMMAND RestrictedValueTest)
