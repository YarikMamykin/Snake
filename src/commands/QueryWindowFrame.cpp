#include "QueryWindowFrame.hpp"
#include "XlibWrapper.hpp"
#include "Settings.hpp"

namespace commands {
  QueryWindowFrame::QueryWindowFrame(abstractions::ui::Object* window, std::atomic<bool>& trigger) 
  : SynchronousCommand(trigger)
  , window(window) { }

  DoSaveResult QueryWindowFrame::execute() {
    auto&& win_attr = xlib::XlibWrapper::self()->get_window_attributes();
    window->set_width(win_attr.width);
    window->set_height(win_attr.height);
    configuration::Settings::get_concrete_ptr<geometry::Rectangle>(configuration::ConfigID::WINDOW_FRAME)->change_value(window->get_frame());
    trigger.store(!trigger.load()); 
    return DoSaveResult::NO;
  }

  constexpr CommandID QueryWindowFrame::get_id() const {
    return CommandID::QueryWindowFrame;
  }
}
