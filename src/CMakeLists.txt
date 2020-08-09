cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/xlib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/interfaces)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/views)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/events)

set(XLIB_UI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_Display.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_Window.cpp
)

set(EVENTS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/events/EventHandler.cpp)

set(GAME_VIEW_SRC ${CMAKE_CURRENT_SOURCE_DIR}/views/GameMenu.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameAction.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameNone.cpp
)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/kek.cpp)

add_library(xlib_ui STATIC ${XLIB_UI_SRC})
add_library(events STATIC ${EVENTS_SRC})
add_library(game_view_src STATIC ${GAME_VIEW_SRC})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(events xlib_ui)
target_link_libraries(${PROJECT_NAME} xlib_ui events game_view_src)
