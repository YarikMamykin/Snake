#ifndef SRC_INCLUDE_GAME_OBJECTS_INFO_HPP
#define SRC_INCLUDE_GAME_OBJECTS_INFO_HPP

#include <memory>
#include <chrono>
#include "xlib/X11_TextLabel.hpp"

namespace game_objects {

  class Info {
    std::unique_ptr<xlib::X11_TextLabel> score, time;

    void update_score(unsigned int new_score);
    void update_time(std::chrono::milliseconds new_time);

    public:
    explicit Info();
    ~Info() = default;
    void update(unsigned int new_score, std::chrono::milliseconds new_time);
  };
}

#endif /* SRC_INCLUDE_GAME_OBJECTS_INFO_HPP */
