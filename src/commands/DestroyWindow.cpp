#include "DestroyWindow.hpp"
#include "XlibWrapper.hpp"

namespace commands {
  DestroyWindow::DestroyWindow() 
  : Command(geometry::Rectangle(), color::Color()) { }

  void DestroyWindow::execute() {
    xlib::XlibWrapper::self()->destroy_window();
  }
}


