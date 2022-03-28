cmake_minimum_required(VERSION 3.0)

set(THREADS_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/XlibThread.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UI_Thread.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ThreadDispatcher.cpp
)

add_library(threads SHARED ${THREADS_SRC})

target_link_libraries(threads 
xlib_ui 
events 
game_views
helpers
timer
game_objects
presenters
color
settings
anchor_handlers
commands
Threads::Threads
)
