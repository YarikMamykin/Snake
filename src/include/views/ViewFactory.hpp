#ifndef SRC_INCLUDE_VIEWS_VIEWFACTORY_HPP
#define SRC_INCLUDE_VIEWS_VIEWFACTORY_HPP
#include "constants/Constants.hpp"
#include "views/GameMenu.hpp"
#include "views/GameAction.hpp"
#include "views/GameAbout.hpp"
#include "views/GameOver.hpp"
#include "views/GameSettings.hpp"
#include "views/GameNone.hpp"

namespace views {
    class ViewFactory {
      public:
        static std::unique_ptr<View> get_view(ViewID id) {
          std::unique_ptr<View> new_view;
          switch(id) {
            case ViewID::ACTION:  new_view.reset(new GameAction); break;
            case ViewID::ABOUT:  new_view.reset(new GameAbout); break;
            case ViewID::MENU:  new_view.reset(new GameMenu); break;
            case ViewID::OVER:  new_view.reset(new GameOver); break;
            case ViewID::SETTINGS:  new_view.reset(new GameSettings); break;
            default:  new_view.reset(new GameNone); break;
          }
          return new_view;
        }
    };
}

#endif /* SRC_INCLUDE_VIEWS_VIEWFACTORY_HPP */
