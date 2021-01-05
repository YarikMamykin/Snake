#include "GameMenu.hpp"
#include "Helper.hpp"
#include "WindowAnchorHandler.hpp"

namespace {
  const std::string NewGameItemName = "New Game"; 
  const std::string ScoreItemName = "Score"; 
  const std::string SettingsItemName = "Settings"; 
  const std::string ExitItemName = "Exit";

  auto empty_key_press_handler = [](const KeySym&& key_sym) {};

  abstractions::ui::COLOR_SCHEME_TYPE text_labels_color_scheme = {
    { ui::ColorSchemeID::BackgroundColor, 0UL },
    { ui::ColorSchemeID::TextColor, (255UL << 8) },
    { ui::ColorSchemeID::FrameColor, (255UL << 16) }
  };
}

namespace views {

  GameMenu::Item::Item(xlib::X11_Window* x_window, 
      const std::string& name, 
      KEY_PRESS_HANDLER_TYPE key_press_handler)
  : xlib::X11_TextLabel(name, {}, text_labels_color_scheme, x_window)
  , key_press_handler(key_press_handler) { }

  GameMenu::Item::~Item() {
  }

  void GameMenu::Item::handle_key_press(const KeySym&& key_sym) {
    if(this->focused()) {
      this->key_press_handler(std::move(key_sym));
    }
  }

  GameMenu::GameMenu(xlib::X11_Window* x_window) 
  : parent_window(x_window) 
  , menu(::ui::LayoutType::VERTICAL, {}, text_labels_color_scheme, x_window) {
    std::unique_ptr<abstractions::ui::Object> menu_item;
    menu_item.reset(new Item(x_window, NewGameItemName, [x_window](const KeySym&& key_sym) {
          switch(key_sym) {
            case XK_Return: helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::ACTION); break;
          }}));
    menu.add_item(std::move(menu_item));

    menu_item.reset(new Item(x_window, ScoreItemName, empty_key_press_handler));
    menu.add_item(std::move(menu_item));

    menu_item.reset(new Item(x_window, SettingsItemName, [x_window](const KeySym&& key_sym) {
          switch(key_sym) {
            case XK_Return: helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::SETTINGS); break;
          }}));
    menu.add_item(std::move(menu_item));
    
    menu_item.reset(new Item(x_window, ExitItemName, [x_window](const KeySym&& key_sym) {
          switch(key_sym) {
            case XK_Return: helpers::Helper::SendExitApplicationEvent(x_window); break;
          }}));
    menu.add_item(std::move(menu_item));
  }

  GameMenu::~GameMenu() {
  }

  void GameMenu::activate() {
    update();
  }

  void GameMenu::update() {
    ui::WindowAnchorHandler<decltype(menu)> anchor_handler(&menu, parent_window);
    menu.get_current_item()->get()->set_focused(true);
    menu.show(true);
  }

  void GameMenu::deactivate() { }

  void GameMenu::handle_key_press(const KeySym&& key_sym) {
    switch(key_sym) {
      case XK_Down: menu.move_to_next_item(); break;
      case XK_Up: menu.move_to_prev_item(); break;
      case XK_Return: 
      {
        current_item_as_key_press_handler(menu)->handle_key_press(std::move(key_sym)); 
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
