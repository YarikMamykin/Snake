#ifndef SRC_INCLUDE_EXCEPTIONS_EXCEPTIONS_HPP
#define SRC_INCLUDE_EXCEPTIONS_EXCEPTIONS_HPP

#include <exception>

namespace exceptions {
    struct ExitApplication : public std::exception {
      const char* what() const noexcept override {
        return "ExitApplication";
      }
    };

    struct ChangeView : public std::exception {
      const char* what() const noexcept override {
        return "ChangeView";
      }
    };

    struct GameOver : public std::exception {
      const char* what() const noexcept override {
        return "GameOver";
      }
    };
}

#endif /* SRC_INCLUDE_EXCEPTIONS_EXCEPTIONS_HPP */
