################################
# GTest
################################
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src/include/abstractions)
include_directories(${CMAKE_SOURCE_DIR}/src/include/constants)
include_directories(${CMAKE_SOURCE_DIR}/src/include/events)
include_directories(${CMAKE_SOURCE_DIR}/src/include/exceptions)
include_directories(${CMAKE_SOURCE_DIR}/src/include/game_objects)
include_directories(${CMAKE_SOURCE_DIR}/src/include/geometry)
include_directories(${CMAKE_SOURCE_DIR}/src/include/helpers)
include_directories(${CMAKE_SOURCE_DIR}/src/include/settings)
include_directories(${CMAKE_SOURCE_DIR}/src/include/timing)
include_directories(${CMAKE_SOURCE_DIR}/src/include/views)
include_directories(${CMAKE_SOURCE_DIR}/src/include/xlib)

################################
# Unit Tests
################################
# Add test cpp file
add_executable( runUnitTests gtestexample.cpp TimerTest.cpp RectangleTest.cpp)
# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main xlib_ui events game_view helpers timer snake)
add_test( runUnitTests runUnitTests )
