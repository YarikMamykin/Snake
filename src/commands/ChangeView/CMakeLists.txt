cmake_minimum_required(VERSION 3.0)

add_library(command_change_view OBJECT 
	${CMAKE_CURRENT_SOURCE_DIR}/ChangeView.cpp
)

add_dependencies(command_change_view helpers)
target_link_libraries(command_change_view helpers)
