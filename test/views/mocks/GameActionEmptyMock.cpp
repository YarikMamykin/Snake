#include "views/GameAction.hpp"

namespace game_objects {
	class Snake {
		public:
			Snake() = default;
			~Snake() = default;
	};

  class FoodGenerator {
		public:
			FoodGenerator() = default;
			~FoodGenerator() = default;
	};

  class MovementController {
		public:
			MovementController() = default;
			~MovementController() = default;
	};

  class Info {
		public:
			Info() = default;
			~Info() = default;
	};
}

namespace timing {
	class Timer {
		public:
			Timer() = default;
			~Timer() = default;
	};
}

namespace views {

	GameAction::GameAction() = default;
	GameAction::~GameAction() = default;

	void GameAction::activate() {}
	void GameAction::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {}

	void GameAction::set_paused(const bool){}
	void GameAction::deactivate(){}

}
