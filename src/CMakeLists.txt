cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(XLIB_UI_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_Window.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_TextLabel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_ColorizedTextLabel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_Menu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/xlib/X11_ColorLabel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/xlib/XlibWrapper.cpp
)

set(EVENTS_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/events/EventDispatcher.cpp
)

set(HELPERS_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/helpers/Helper.cpp
)

set(GAME_VIEW_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameMenu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameAction.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameAbout.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameOver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameSettings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/views/GameNone.cpp
)

set(TIMER_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/timing/Timer.cpp
)

set(GAME_OBJECTS_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/game_objects/Snake.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/game_objects/MovementController.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/game_objects/Food.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/game_objects/FoodGenerator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/game_objects/Info.cpp
)

set(PRESENTERS_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/ui/ColorValuePresenter.cpp
)

set(COLOR_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/color/Color.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/color/ColorPallete.cpp
)

set(SETTINGS_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/configuration/Settings.cpp
)

set(ANCHOR_HANDLERS
  ${CMAKE_CURRENT_SOURCE_DIR}/anchor_handlers/CenterWindowAnchorHandler.cpp
)

set(COMMANDS_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/commands/Command.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/commands/graphics_commands/DrawCircle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/commands/graphics_commands/DrawRectangle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/commands/graphics_commands/DrawText.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/commands/graphics_commands/FillCircle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/commands/graphics_commands/FillRectangle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/commands/synchronous_commands/QueryTextWidth.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/commands/synchronous_commands/QueryTextHeight.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/commands/synchronous_commands/QueryWindowFrame.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/commands/ChangeView.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/commands/ExitApplication.cpp
)

set(THREADS_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/threads/XlibThread.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/threads/UI_Thread.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/threads/ThreadDispatcher.cpp
 )

add_library(xlib_ui SHARED ${XLIB_UI_SRC})
add_library(events SHARED ${EVENTS_SRC})
add_library(game_views SHARED ${GAME_VIEW_SRC})
add_library(helpers SHARED ${HELPERS_SRC})
add_library(timer SHARED ${TIMER_SRC})
add_library(game_objects SHARED ${GAME_OBJECTS_SRC})
add_library(presenters SHARED ${PRESENTERS_SRC})
add_library(color SHARED ${COLOR_SRC})
add_library(anchor_handlers SHARED ${ANCHOR_HANDLERS})
add_library(commands SHARED ${COMMANDS_SRC})
add_library(settings SHARED ${SETTINGS_SRC})
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
)


add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/kek.cpp)
target_link_libraries(${PROJECT_NAME} 
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
threads
)


if(${UNIT_TESTS})
  add_subdirectory(test)
endif()
