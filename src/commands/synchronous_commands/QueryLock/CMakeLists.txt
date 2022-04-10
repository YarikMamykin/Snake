cmake_minimum_required(VERSION 3.0)

add_library(query_lock OBJECT
  ${CMAKE_CURRENT_SOURCE_DIR}/QueryLock.cpp
)
