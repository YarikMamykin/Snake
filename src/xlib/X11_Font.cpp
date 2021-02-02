#include "X11_Font.hpp"
#include "XlibWrapper.hpp"


namespace xlib {
  X11_Font::X11_Font(const char* font_name) {
    XlibWrapper::self()->load_font(font_name);
  }

  X11_Font::~X11_Font() {
    XlibWrapper::self()->free_font();
  }
}
