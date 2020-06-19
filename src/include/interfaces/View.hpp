#ifndef SRC_INCLUDE_INTERFACES_VIEWS_HPP
#define SRC_INCLUDE_INTERFACES_VIEWS_HPP

namespace views {

  class View {
    public:
    virtual void activate() = 0;
    virtual void deactivate() = 0;
  };
}

#endif /* SRC_INCLUDE_INTERFACES_VIEWS_HPP */
