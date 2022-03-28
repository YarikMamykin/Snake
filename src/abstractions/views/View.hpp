#ifndef SRC_INCLUDE_ABSTRACTIONS_VIEWS_VIEW_HPP
#define SRC_INCLUDE_ABSTRACTIONS_VIEWS_VIEW_HPP
#include <memory>

namespace views {

  class View {
    public:
      virtual void activate() = 0;
      virtual ~View() {};
  };
}


#endif /* SRC_INCLUDE_ABSTRACTIONS_VIEWS_VIEW_HPP */
