cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/xlib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/interfaces)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/views)

set(XLIB_UI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_Display.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_Window.cpp
)

set(GAME_VIEW_SRC ${CMAKE_CURRENT_SOURCE_DIR}/views/GameMenu.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameAction.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameNone.cpp
)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/kek.cpp)

add_library(xlib_ui STATIC ${XLIB_UI_SRC})
add_library(game_view_src STATIC ${GAME_VIEW_SRC})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} xlib_ui game_view_src)
