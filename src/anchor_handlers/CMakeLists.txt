cmake_minimum_required(VERSION 3.0)

set(ANCHOR_HANDLERS
  ${CMAKE_CURRENT_SOURCE_DIR}/CenterWindowAnchorHandler.cpp
)

add_library(anchor_handlers SHARED ${ANCHOR_HANDLERS})
