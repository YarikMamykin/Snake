cmake_minimum_required(VERSION 3.0)

add_library(command_exit_application OBJECT 
	${CMAKE_CURRENT_SOURCE_DIR}/ExitApplication.cpp
)

add_dependencies(command_exit_application helpers)
target_link_libraries(command_exit_application helpers)
