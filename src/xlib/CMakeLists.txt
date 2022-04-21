cmake_minimum_required(VERSION 3.0)

add_subdirectory(XProxy)

add_subdirectory(X11_ColorLabel)
add_subdirectory(X11_ColorizedTextLabel)
add_subdirectory(X11_Menu)
add_subdirectory(X11_TextLabel)
add_subdirectory(X11_Window)

add_library(xlib_ui SHARED 
  $<TARGET_OBJECTS:x11_color_label>
  $<TARGET_OBJECTS:x11_colorized_text_label>
  $<TARGET_OBJECTS:x11_menu>
  $<TARGET_OBJECTS:x11_text_label>
  $<TARGET_OBJECTS:x11_window>
)

set(DEPS 
  xproxy
  command_query_window_frame
  command_query_text_height
  command_query_text_width
  command_fill_rectangle
  command_fill_circle
  command_draw_rectangle
  command_draw_text
  query_lock
)

add_dependencies(xlib_ui ${DEPS})

target_link_libraries(xlib_ui ${DEPS})
install(TARGETS xlib_ui RUNTIME DESTINATION lib)
