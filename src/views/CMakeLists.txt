cmake_minimum_required(VERSION 3.0)


add_subdirectory(GameAbout)
add_subdirectory(GameAction)
add_subdirectory(GameMenu)
add_subdirectory(GameNone)
add_subdirectory(GameOver)
add_subdirectory(GameSettings)

add_library(game_views SHARED 
  $<TARGET_OBJECTS:view_game_about>
  $<TARGET_OBJECTS:view_game_action>
  $<TARGET_OBJECTS:view_game_menu>
  $<TARGET_OBJECTS:view_game_none>
  $<TARGET_OBJECTS:view_game_over>
  $<TARGET_OBJECTS:view_game_settings>
)
