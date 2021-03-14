#include "CenterWindowAnchorHandler.hpp"
#include "QueryWindowAttributes.hpp"

namespace ui {
  CenterWindowAnchorHandler::CenterWindowAnchorHandler(abstractions::ui::Object* object) {
    object->set_center(get_window_center());
  }

  geometry::Point CenterWindowAnchorHandler::get_window_center() {
    commands::Command::push_xlib_command(new commands::QueryWindowAttributes());
    std::unique_ptr<commands::Command> win_attr_command_result = commands::Command::get_command_with_result(commands::CommandID::QueryWindowAttributes);
    const auto& win_attr = dynamic_cast<commands::QueryWindowAttributes*>(win_attr_command_result.get())->get_window_attributes();
    return { .x = win_attr.width/2, .y = win_attr.height/2 };
  }
}
