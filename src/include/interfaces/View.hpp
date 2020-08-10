#ifndef SRC_INCLUDE_INTERFACES_VIEWS_HPP
#define SRC_INCLUDE_INTERFACES_VIEWS_HPP

#include <memory>

namespace views {

  class View {
    public:
      virtual void activate() = 0;
      virtual void deactivate() = 0;
      template <class EventHandlerType> static EventHandlerType* as_event_handler(std::shared_ptr<View> view) {
        return dynamic_cast<EventHandlerType*>(view.get());
      }
      virtual ~View() {};
  };
}

#endif /* SRC_INCLUDE_INTERFACES_VIEWS_HPP */
