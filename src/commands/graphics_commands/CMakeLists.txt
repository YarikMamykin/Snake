cmake_minimum_required(VERSION 3.0)


add_subdirectory(DrawCircle)
add_subdirectory(DrawRectangle)
add_subdirectory(DrawText)
add_subdirectory(FillCircle)
add_subdirectory(FillRectangle)


add_library(graphics_commands OBJECT 
  $<TARGET_OBJECTS:command_draw_circle>
  $<TARGET_OBJECTS:command_draw_rectangle>
  $<TARGET_OBJECTS:command_draw_text>
  $<TARGET_OBJECTS:command_fill_circle>
  $<TARGET_OBJECTS:command_fill_rectangle>
)
