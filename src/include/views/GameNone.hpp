#ifndef SRC_INCLUDE_VIEWS_GAMENONE_HPP
#define SRC_INCLUDE_VIEWS_GAMENONE_HPP

#include "UI_Object.hpp"
#include "View.hpp"

namespace views {

  class GameNone final :  public ui::UI_Object,
                          public View {
    public:
      explicit GameNone();
      virtual ~GameNone();

    public:
      virtual void activate() override;
      virtual void deactivate() override;
      const int get_event_handling_mask() const override;
  };
}


#endif /* SRC_INCLUDE_VIEWS_GAMENONE_HPP */
