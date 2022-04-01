cmake_minimum_required(VERSION 3.0)

add_subdirectory(X11_ColorLabel)
add_subdirectory(X11_ColorizedTextLabel)
add_subdirectory(X11_Menu)
add_subdirectory(X11_TextLabel)
add_subdirectory(X11_Window)
add_subdirectory(XProxy)

add_library(xlib_ui SHARED 
  $<TARGET_OBJECTS:x11_color_label>
  $<TARGET_OBJECTS:x11_colorized_text_label>
  $<TARGET_OBJECTS:x11_menu>
  $<TARGET_OBJECTS:x11_text_label>
  $<TARGET_OBJECTS:x11_window>
  $<TARGET_OBJECTS:xproxy>
)
