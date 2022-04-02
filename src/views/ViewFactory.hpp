#ifndef SRC_INCLUDE_VIEWS_VIEWFACTORY_HPP
#define SRC_INCLUDE_VIEWS_VIEWFACTORY_HPP
#include "constants/Constants.hpp"
#include "views/GameMenu/GameMenu.hpp"
#include "views/GameAction/GameAction.hpp"
#include "views/GameAbout/GameAbout.hpp"
#include "views/GameOver/GameOver.hpp"
#include "views/GameSettings/GameSettings.hpp"
#include "views/GameNone/GameNone.hpp"
#include <memory>

namespace views {
    class ViewFactory {
      public:
        static std::unique_ptr<View> get_view(ViewID id) {
          switch(id) {
            case ViewID::ACTION:    return std::make_unique<GameAction>(); 
            case ViewID::ABOUT:     return std::make_unique<GameAbout>(); 
            case ViewID::MENU:      return std::make_unique<GameMenu>(); 
            case ViewID::OVER:      return std::make_unique<GameOver>();
            case ViewID::SETTINGS:  return std::make_unique<GameSettings>();
            default: break;
          }
          return std::make_unique<GameNone>();
        }
    };
}

#endif /* SRC_INCLUDE_VIEWS_VIEWFACTORY_HPP */
