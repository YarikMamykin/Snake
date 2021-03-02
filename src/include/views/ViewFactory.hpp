#ifndef SRC_INCLUDE_VIEWS_VIEWFACTORY_HPP
#define SRC_INCLUDE_VIEWS_VIEWFACTORY_HPP

#include "Constants.hpp"
#include "GameMenu.hpp"
#include "GameAction.hpp"
#include "GameAbout.hpp"
#include "GameOver.hpp"
#include "GameSettings.hpp"
#include "GameNone.hpp"

namespace views {
    class ViewFactory {
      public:
        static std::shared_ptr<View> get_view(ViewID id, xlib::X11_Window* parent_window) {
          switch(id) {
            case ViewID::ACTION:  new_view.reset(new GameAction(parent_window)); break;
            case ViewID::ABOUT:  new_view.reset(new GameAbout(parent_window)); break;
            case ViewID::MENU:  new_view.reset(new GameMenu(parent_window)); break;
            case ViewID::OVER:  new_view.reset(new GameOver(parent_window)); break;
            case ViewID::SETTINGS:  new_view.reset(new GameSettings(parent_window)); break;
            default:  new_view.reset(new GameNone(parent_window)); break;
          }
          return new_view;
        }
    };
}
#endif /* SRC_INCLUDE_VIEWS_VIEWFACTORY_HPP */
