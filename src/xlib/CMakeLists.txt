cmake_minimum_required(VERSION 3.0)

set(XLIB_UI_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/X11_Window.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/X11_TextLabel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/X11_ColorizedTextLabel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/X11_Menu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/X11_ColorLabel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/XProxy.cpp
)

add_library(xlib_ui SHARED ${XLIB_UI_SRC})
