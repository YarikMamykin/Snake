cmake_minimum_required(VERSION 3.0)

add_subdirectory(color)

add_subdirectory(xlib)

add_subdirectory(helpers)

add_subdirectory(commands)

add_subdirectory(events)

add_subdirectory(views)

add_subdirectory(timing)

add_subdirectory(game_objects)

add_subdirectory(ui)

add_subdirectory(configuration)

add_subdirectory(anchor_handlers)

add_subdirectory(threads)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} 
xlib_ui 
events 
game_views
timer
game_objects
presenters
color
settings
anchor_handlers
commands
threads
)
