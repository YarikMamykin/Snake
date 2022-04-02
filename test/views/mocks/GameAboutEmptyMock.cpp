#include "gmock/gmock.h"
#include "views/GameAbout/GameAbout.hpp"

namespace views {

	GameAbout::GameAbout() = default;

	void GameAbout::activate() {}
	void GameAbout::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {}
}
