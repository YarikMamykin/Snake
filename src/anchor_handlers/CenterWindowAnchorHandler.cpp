#include "CenterWindowAnchorHandler.hpp"
#include "Settings.hpp"

namespace ui {
  CenterWindowAnchorHandler::CenterWindowAnchorHandler(abstractions::ui::Object* object) {
    object->set_center(get_window_center());
  }

  geometry::Point CenterWindowAnchorHandler::get_window_center() {
    const auto&& win_frame = configuration::Settings::get_concrete<geometry::Rectangle>(configuration::ConfigID::WINDOW_FRAME);
    return { .x = win_frame.width/2u, .y = win_frame.height/2u };
  }
}
