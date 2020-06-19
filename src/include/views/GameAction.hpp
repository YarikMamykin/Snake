#ifndef SRC_INCLUDE_VIEWS_GAMEACTION_HPP
#define SRC_INCLUDE_VIEWS_GAMEACTION_HPP

#include "View.hpp"

namespace views {

  class GameAction : public View {
    public:
      explicit GameAction();
      virtual ~GameAction();

    public:
      virtual void activate() override;
      virtual void deactivate() override;
  };

}
#endif /* SRC_INCLUDE_VIEWS_GAMEACTION_HPP */
