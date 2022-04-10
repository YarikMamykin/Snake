#include "QueryWindowFrame.hpp"
#include "configuration/Settings.hpp"
#include <xlib/XProxy/XProxy.hpp>

namespace commands {
  QueryWindowFrame::QueryWindowFrame(
      abstractions::ui::Object* window, 
      QueryLock& ql) 
  : SynchronousCommand(ql)
  , window(window) { }

  void QueryWindowFrame::execute(xlib::XProxy& proxy) {
    auto&& win_attr = proxy.get_window_attributes();
    window->set_width(win_attr.width);
    window->set_height(win_attr.height);
    config::get_concrete_ref<geometry::Rectangle>(config_id::WINDOW_FRAME) = window->get_frame();
  }

}
