cmake_minimum_required(VERSION 3.0)

add_subdirectory(Food)
add_subdirectory(FoodGenerator)
add_subdirectory(Info)
add_subdirectory(MovementController)
add_subdirectory(Snake)

add_library(game_objects SHARED 
  $<TARGET_OBJECTS:game_object_food>
  $<TARGET_OBJECTS:game_object_food_generator>
  $<TARGET_OBJECTS:game_object_info>
  $<TARGET_OBJECTS:game_object_movement_controller>
  $<TARGET_OBJECTS:game_object_snake>
)
