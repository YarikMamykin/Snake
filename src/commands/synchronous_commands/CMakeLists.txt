cmake_minimum_required(VERSION 3.0)

add_subdirectory(QueryLock)
add_subdirectory(QueryTextHeight)
add_subdirectory(QueryTextWidth)
add_subdirectory(QueryWindowFrame)

add_library(synchronous_commands OBJECT 
  $<TARGET_OBJECTS:query_lock>
  $<TARGET_OBJECTS:command_query_text_height>
  $<TARGET_OBJECTS:command_query_text_width>
  $<TARGET_OBJECTS:command_query_window_frame>
)

