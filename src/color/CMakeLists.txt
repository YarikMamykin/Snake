cmake_minimum_required(VERSION 3.0)

add_subdirectory(Color)
add_subdirectory(ColorPallete)

add_library(color SHARED
  $<TARGET_OBJECTS:color_impl>
  $<TARGET_OBJECTS:color_pallete>
)
