cmake_minimum_required(VERSION 3.0)

add_library(xproxy SHARED 
  ${CMAKE_CURRENT_SOURCE_DIR}/XProxy.cpp
)
install(TARGETS xproxy RUNTIME DESTINATION lib)
