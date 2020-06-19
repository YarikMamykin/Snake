#ifndef SRC_INCLUDE_VIEWS_GAMEMENU_HPP
#define SRC_INCLUDE_VIEWS_GAMEMENU_HPP

#include "View.hpp"

namespace views {

  class GameMenu : public View {
    public:
      explicit GameMenu();
      explicit GameMenu(GameMenu&& game_menu) = default;
      virtual ~GameMenu();

    public:
      virtual void activate() override;
      virtual void deactivate() override;
  };
}

#endif /* SRC_INCLUDE_VIEWS_GAMEMENU_HPP */
