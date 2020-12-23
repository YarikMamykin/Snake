cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/abstractions)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/abstractions/event_handling)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/constants)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/events)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/exceptions)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/game_objects)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/geometry)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/helpers)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/settings)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/timing)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/views)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/xlib)

set(XLIB_UI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_Display.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_Window.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_TextLabel.cpp
)

set(EVENTS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/events/EventHandler.cpp)

set(HELPERS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/helpers/Helper.cpp)

set(GAME_VIEW_SRC ${CMAKE_CURRENT_SOURCE_DIR}/views/GameMenu.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameAction.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameOver.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameSettings.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameNone.cpp
)

set(TIMER_SRC ${CMAKE_CURRENT_SOURCE_DIR}/timing/Timer.cpp)
set(SNAKE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/game_objects/Snake.cpp)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/kek.cpp)

add_library(xlib_ui STATIC ${XLIB_UI_SRC})
add_library(events STATIC ${EVENTS_SRC})
add_library(game_view STATIC ${GAME_VIEW_SRC})
add_library(helpers STATIC ${HELPERS_SRC})
add_library(timer STATIC ${TIMER_SRC})
add_library(snake STATIC ${SNAKE_SRC})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(events xlib_ui)
target_link_libraries(${PROJECT_NAME} xlib_ui events game_view helpers timer snake)
