cmake_minimum_required(VERSION 3.0)

set(PRESENTERS_SRC 
  ${CMAKE_CURRENT_SOURCE_DIR}/ColorValuePresenter.cpp
)

add_library(presenters SHARED ${PRESENTERS_SRC})
