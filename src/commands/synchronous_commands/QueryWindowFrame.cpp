#include "QueryWindowFrame.hpp"
#include "XlibWrapper.hpp"
#include "Settings.hpp"

namespace commands {
  QueryWindowFrame::QueryWindowFrame(abstractions::ui::Object* window, std::atomic<bool>& trigger) 
  : SynchronousCommand(trigger)
  , window(window) { }

  void QueryWindowFrame::execute() {
    auto&& win_attr = xlib::XlibWrapper::self()->get_window_attributes();
    window->set_width(win_attr.width);
    window->set_height(win_attr.height);
    config::get_concrete_ref<geometry::Rectangle>(config_id::WINDOW_FRAME) = window->get_frame();
    trigger.store(!trigger.load()); 
  }

}
