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
  : parent_window(x_window) {
    items.emplace_back(Item(x_window, NewGameItemName, [x_window](const KeySym&& key_sym) {
          switch(key_sym) {
            case XK_Return: helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::ACTION); break;
          }}));
    items.emplace_back(Item(x_window, ScoreItemName, empty_key_press_handler));
    items.emplace_back(Item(x_window, SettingsItemName, [x_window](const KeySym&& key_sym) {
          switch(key_sym) {
            case XK_Return: helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::SETTINGS); break;
          }}));
    items.emplace_back(Item(x_window, ExitItemName, [x_window](const KeySym&& key_sym) {
          switch(key_sym) {
            case XK_Return: helpers::Helper::SendExitApplicationEvent(x_window); break;
          }}));

    current_item = items.begin();
    current_item->set_focused(true);

    for(auto& item : items) {
      items_layout.add(&item);
    }
  }

  GameMenu::~GameMenu() {
  }

  void GameMenu::activate() {
    update();
  }

  void GameMenu::update() {
    current_item->set_focused(true);
    ui::WindowAnchorHandler<decltype(items_layout)> anchor_handler(&items_layout, parent_window);
    items_layout.update();
  }

  void GameMenu::deactivate() { }

  void GameMenu::handle_key_press(const KeySym&& key_sym) {
    switch(key_sym) {
      case XK_Down: move_to_next_item(); break;
      case XK_Up: move_to_prev_item(); break;
      case XK_Return: current_item->handle_key_press(std::move(key_sym)); break; 
    }

    update();
  }

  void GameMenu::move_to_next_item() {
    for(auto& item : items) {
      item.set_focused(false);
    }

    if(current_item == --items.end()) {
      current_item = items.begin();
      return;
    }

    current_item = std::next(current_item);
    return;
  }

  void GameMenu::move_to_prev_item() {
    for(auto& item : items) {
      item.set_focused(false);
    }

    if(current_item == items.begin()) {
      current_item = --items.end();
      return;
    }

    current_item = std::prev(current_item);
    return;
  }

  const int GameMenu::get_event_handling_mask() const {
    return events::KeyPressHandler::get_event_handling_mask();
  }
}
