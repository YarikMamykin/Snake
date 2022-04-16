cmake_minimum_required(VERSION 3.0)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/MockXProxy)

add_subdirectory(MockXProxy)

add_subdirectory(QueryLock)
add_subdirectory(ChangeView)
add_subdirectory(ExitApplication)
add_subdirectory(graphics_commands)
add_subdirectory(synchronous_commands)
