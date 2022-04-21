cmake_minimum_required(VERSION 3.0)

add_library(test_xproxy SHARED 
  ${CMAKE_CURRENT_SOURCE_DIR}/XProxy.cpp
)
install(TARGETS test_xproxy RUNTIME DESTINATION lib)
