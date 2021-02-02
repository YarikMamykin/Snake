#ifndef SRC_INCLUDE_XLIB_X11_FONT_HPP
#define SRC_INCLUDE_XLIB_X11_FONT_HPP

#include "XHeaders.hpp"
#include <string>

namespace xlib {
  struct X11_Font {
    X11_Font(const char* font_name);
    ~X11_Font();
  };
}


#endif /* SRC_INCLUDE_XLIB_X11_FONT_HPP */
