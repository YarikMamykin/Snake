#include "GameNone.hpp"

namespace views {

  GameNone::GameNone() {
  }

  GameNone::~GameNone() {
  }

  void GameNone::activate() {

  }

  void GameNone::deactivate() {
  }

  const int GameNone::get_event_handling_mask() const {
    return 0;
  }
}
