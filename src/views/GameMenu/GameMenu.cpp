#include "GameMenu.hpp"
#include "helpers/Helper.hpp"
#include "anchor_handlers/CenterWindowAnchorHandler.hpp"
#include "color/Color.hpp"
#include "commands/ChangeView/ChangeView.hpp"
#include "commands/ExitApplication/ExitApplication.hpp"
#include "xlib/X11_Menu/X11_Menu.hpp"

namespace {
  const std::string NewGameItemName = "New Game"; 
  const std::string AboutItemName = "About"; 
  const std::string SettingsItemName = "Settings"; 
  const std::string ExitItemName = "Exit";

  color::COLOR_SCHEME_TYPE text_labels_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::TextColor, (255UL << 8) },
    { color::ColorSchemeID::FrameColor, (255UL << 16) }
  };
}

namespace views {

  GameMenu::Item::Item(const std::string& name, std::function<void()> activation_callback)
  : xlib::X11_TextLabel(name, {}, text_labels_color_scheme)
  , activation_callback(activation_callback) { }

  void GameMenu::Item::activate() {
    if(this->focused()) {
      this->activation_callback();
    }
  }

  GameMenu::GameMenu() 
  : menu(new xlib::X11_Menu(::ui::LayoutType::VERTICAL, {}, text_labels_color_scheme)) {
    menu->add_item(std::make_unique<Item>(NewGameItemName, []() { commands::Command::push_xlib_command(std::make_unique<commands::ChangeView>(views::ViewID::ACTION)); }));
    menu->add_item(std::make_unique<Item>(SettingsItemName, []() { commands::Command::push_xlib_command(std::make_unique<commands::ChangeView>(views::ViewID::SETTINGS)); }));
    menu->add_item(std::make_unique<Item>(AboutItemName, []() { commands::Command::push_xlib_command(std::make_unique<commands::ChangeView>(views::ViewID::ABOUT)); }));
    menu->add_item(std::make_unique<Item>(ExitItemName, []() { commands::Command::push_xlib_command(std::make_unique<commands::ExitApplication>()); }));
  }

  void GameMenu::activate() {
    update();
  }

  void GameMenu::update() {
    ui::CenterWindowAnchorHandler anchor_handler(menu.get());
    menu->get_current_item()->get()->set_focused(true);
    menu->show(true);
  }

  void GameMenu::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {
    switch(key_sym) {
      case XK_Down: menu->move_to_next_item(); break;
      case XK_Up: menu->move_to_prev_item(); break;
      case XK_Return: current_item_as_game_menu_item(*menu)->activate(); break; 
    }

    update();
  }

  GameMenu::Item* GameMenu::current_item_as_game_menu_item(const abstractions::ui::Menu& menu) {
    return static_cast<GameMenu::Item*>(menu.get_current_item()->get());
  }
}
