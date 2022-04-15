cmake_minimum_required(VERSION 3.0)

add_executable(FoodTest
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/FoodTest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MockFillCircle.cpp
)
target_link_libraries(FoodTest
  gtest
  gtest_main
  gmock
  game_object_food 
  timer
  color
  settings
)
add_test(NAME FoodTest COMMAND FoodTest)
