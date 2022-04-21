cmake_minimum_required(VERSION 3.0)

add_compile_options(
  -Wall
  -fPIC
  -rdynamic
  -O3
)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
