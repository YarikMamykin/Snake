#pragma once

namespace xlib {
  enum class XError {
    NONE,
    OPEN_DISPLAY_ERROR,
    INIT_SCREEN_ERROR,
    FONT_LOAD_ERROR,
    CREATE_GRAPHICAL_CONTEXT_ERROR,
    CREATE_WINDOW_ERROR
  };
}
