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
            case ViewID::ACTION: return std::make_shared<GameAction>(parent_window); break;
            case ViewID::ABOUT: return std::make_shared<GameAbout>(parent_window); break;
            case ViewID::MENU: return std::make_shared<GameMenu>(parent_window); break;
            case ViewID::OVER: return std::make_shared<GameOver>(parent_window); break;
            case ViewID::SETTINGS: return std::make_shared<GameSettings>(parent_window); break;
            default: return std::make_shared<GameNone>(); break;
          }
        }
    };
}
#endif /* SRC_INCLUDE_VIEWS_VIEWFACTORY_HPP */
