#pragma once

#include "XHeaders.hpp"

namespace xlib {
  struct XHandlers {
    Display* display;
    int screen;
    GC graphical_context;
    Window window;
    XFontStruct* font_info;
  };
}
