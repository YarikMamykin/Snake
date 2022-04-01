cmake_minimum_required(VERSION 3.0)

set(COMMANDS_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/Command.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/graphics_commands/DrawCircle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/graphics_commands/DrawRectangle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/graphics_commands/DrawText.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/graphics_commands/FillCircle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/graphics_commands/FillRectangle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/synchronous_commands/QueryTextWidth.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/synchronous_commands/QueryTextHeight.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/synchronous_commands/QueryWindowFrame.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ChangeView.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ExitApplication.cpp
)

add_library(commands SHARED ${COMMANDS_SRC})
add_dependencies(commands helpers)
target_link_libraries(commands helpers)
