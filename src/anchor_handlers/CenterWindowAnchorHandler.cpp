#include "CenterWindowAnchorHandler.hpp"
#include "XlibWrapper.hpp"

namespace ui {
  CenterWindowAnchorHandler::CenterWindowAnchorHandler(abstractions::ui::Object* object) {
    object->set_center(get_window_center());
  }

  geometry::Point CenterWindowAnchorHandler::get_window_center() {
    auto&& win_attr = xlib::XlibWrapper::self()->get_window_attributes();
    return { .x = win_attr.width/2, .y = win_attr.height/2 };
  }
}
