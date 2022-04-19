#pragma once
#include <memory>

namespace views {

  class View {
    public:
      virtual void activate() = 0;
      virtual ~View() {};
  };
}


