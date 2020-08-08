#ifndef SRC_INCLUDE_VIEWS_GAMENONE_HPP
#define SRC_INCLUDE_VIEWS_GAMENONE_HPP

#include "View.hpp"

namespace views {

  class GameNone : public View {
    public:
      explicit GameNone();
      virtual ~GameNone();

    public:
      virtual void activate() override;
      virtual void deactivate() override;
  };
}


#endif /* SRC_INCLUDE_VIEWS_GAMENONE_HPP */
