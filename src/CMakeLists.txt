cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/xlib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/interfaces)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/views)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_Display.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_Window.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/views/GameMenu.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/views/GameAction.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/kek.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
