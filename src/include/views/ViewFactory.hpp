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
