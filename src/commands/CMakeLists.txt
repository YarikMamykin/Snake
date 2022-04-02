cmake_minimum_required(VERSION 3.0)

add_subdirectory(Command)

add_subdirectory(ChangeView)

add_subdirectory(ExitApplication)

add_subdirectory(graphics_commands)

add_subdirectory(synchronous_commands)


add_library(commands SHARED 
  $<TARGET_OBJECTS:command>
  $<TARGET_OBJECTS:command_change_view>
  $<TARGET_OBJECTS:command_exit_application>
  $<TARGET_OBJECTS:graphics_commands>
  $<TARGET_OBJECTS:synchronous_commands>
)

set(DEPS 
  xproxy
  helpers
)

add_dependencies(commands ${DEPS})
target_link_libraries(commands ${DEPS})
