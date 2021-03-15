#include "GameMenu.hpp"
#include "Helper.hpp"
#include "CenterWindowAnchorHandler.hpp"
#include "Color.hpp"
#include "ChangeView.hpp"
#include "ExitApplication.hpp"

namespace {
  const std::string NewGameItemName = "New Game"; 
  const std::string AboutItemName = "About"; 
  const std::string SettingsItemName = "Settings"; 
  const std::string ExitItemName = "Exit";

  auto empty_key_press_handler = [](const KeySym&& key_sym) {};

  color::COLOR_SCHEME_TYPE text_labels_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::TextColor, (255UL << 8) },
    { color::ColorSchemeID::FrameColor, (255UL << 16) }
  };
}

namespace views {

  GameMenu::Item::Item(const std::string& name, 
      KEY_PRESS_HANDLER_TYPE key_press_handler)
  : xlib::X11_TextLabel(name, {}, text_labels_color_scheme)
  , key_press_handler(key_press_handler) { }

  GameMenu::Item::~Item() {
  }

  void GameMenu::Item::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {
    if(this->focused()) {
      this->key_press_handler(std::move(key_sym));
    }
  }

  GameMenu::GameMenu() 
  : menu(::ui::LayoutType::VERTICAL, {}, text_labels_color_scheme) {
    std::unique_ptr<abstractions::ui::Object> menu_item;
    menu_item.reset(new Item(NewGameItemName, [](const KeySym&& key_sym) {
          switch(key_sym) {
            case XK_Return: commands::Command::push_xlib_command(new commands::ChangeView(views::ViewID::ACTION)); break;
          }}));
    menu.add_item(std::move(menu_item));

    menu_item.reset(new Item(SettingsItemName, [](const KeySym&& key_sym) {
          switch(key_sym) {
            case XK_Return: commands::Command::push_xlib_command(new commands::ChangeView(views::ViewID::SETTINGS)); break;
          }}));
    menu.add_item(std::move(menu_item));

    menu_item.reset(new Item(AboutItemName, [](const KeySym&& key_sym) {
          switch(key_sym) {
            case XK_Return: commands::Command::push_xlib_command(new commands::ChangeView(views::ViewID::ABOUT)); break;
          }}));
    menu.add_item(std::move(menu_item));
    
    menu_item.reset(new Item(ExitItemName, [](const KeySym&& key_sym) {
          switch(key_sym) {
            case XK_Return: commands::Command::push_xlib_command(new commands::ExitApplication()); break;
          }}));
    menu.add_item(std::move(menu_item));
  }

  GameMenu::~GameMenu() {
  }

  void GameMenu::activate() {
    update();
  }

  void GameMenu::update() {
    ui::CenterWindowAnchorHandler anchor_handler(&menu);
    menu.get_current_item()->get()->set_focused(true);
    menu.show(true);
  }

  void GameMenu::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {
    switch(key_sym) {
      case XK_Down: menu.move_to_next_item(); break;
      case XK_Up: menu.move_to_prev_item(); break;
      case XK_Return: 
      {
        current_item_as_key_press_handler(menu)->handle_key_press(key_sym, mask); 
        break; 
      }
    }

    update();
  }

  events::KeyPressHandler* GameMenu::current_item_as_key_press_handler(const xlib::X11_Menu& menu) {
    return static_cast<GameMenu::Item*>(menu.get_current_item()->get());
  }

  const int GameMenu::get_event_handling_mask() const {
    return events::KeyPressHandler::get_event_handling_mask();
  }
}
