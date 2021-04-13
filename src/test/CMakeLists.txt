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
# Add test cpp file
add_executable( runUnitTests
  TimerTest.cpp
  RectangleTest.cpp
  PointTest.cpp
  ColorTest.cpp
  ColorPalleteTest.cpp
  RestrictedValueTest.cpp
)

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests
gtest
gtest_main
xlib_ui 
events 
game_view
helpers
timer
game_objects
presenters
color
settings
anchor_handlers
commands
threads
)
add_test( runUnitTests runUnitTests )
