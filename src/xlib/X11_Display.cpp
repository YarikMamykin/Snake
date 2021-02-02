#include "X11_Display.hpp"
#include "XlibWrapper.hpp"


namespace xlib {
  X11_Display::X11_Display() {
    XlibWrapper::self()->open_display();
  }

  X11_Display::~X11_Display() {
    XlibWrapper::self()->close_display();
  }
}
