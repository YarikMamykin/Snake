cmake_minimum_required(VERSION 3.0)

add_executable(ViewsTest
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ViewFactoryTest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/mocks/GameAboutEmptyMock.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/mocks/GameActionEmptyMock.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/mocks/GameMenuEmptyMock.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/mocks/GameNoneEmptyMock.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/mocks/GameOverEmptyMock.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/mocks/GameSettingsEmptyMock.cpp
)
target_link_libraries(ViewsTest
  gtest
  gtest_main
  gmock
)
add_test(NAME ViewsTest COMMAND ViewsTest)
