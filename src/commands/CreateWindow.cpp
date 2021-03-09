#include "CreateWindow.hpp"
#include "XlibWrapper.hpp"

namespace commands {
  CreateWindow::CreateWindow(geometry::Rectangle&& window_frame, color::COLOR_SCHEME_TYPE&& color_scheme, const char* name) 
  : Command(window_frame, color::Color()) 
  , color_scheme(color_scheme)
  , name(name) { }

  void CreateWindow::execute() {
    xlib::XlibWrapper::self()->create_window(std::forward<decltype(rectangle)>(rectangle), 
                                             std::forward<decltype(color_scheme)>(color_scheme), 
                                             name);
  }
}


