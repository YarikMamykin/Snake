#ifndef SRC_INCLUDE_INTERFACES_VIEWS_HPP
#define SRC_INCLUDE_INTERFACES_VIEWS_HPP

#include <memory>
#include "UI_Object.hpp"

namespace views {

  class View : public ui::UI_Object {
    public:
      virtual void activate() = 0;
      virtual void deactivate() = 0;
      virtual ~View() {};
  };
}

#endif /* SRC_INCLUDE_INTERFACES_VIEWS_HPP */
