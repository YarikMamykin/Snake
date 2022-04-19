#include "gmock/gmock.h"
#include "views/GameSettings/GameSettings.hpp"
#include "MenuEmptyMock.hpp"

namespace views {
  struct Setting { };
}

namespace views {
  GameSettings::GameSettings() {} 
  void GameSettings::activate() {} 
  void GameSettings::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {}

  void GameSettings::update() {}
  Setting* GameSettings::current_item_as_setting(const abstractions::ui::Menu& menu) {return nullptr;}
}

