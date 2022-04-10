#pragma once 

#include <functional>
#include <future>
#include <list>

namespace abstractions::ui {
  class AWindow;
}

namespace threads {

  class UI_Thread { 

    private:
      std::future<void> m_handler;

    public:
      explicit UI_Thread();
      ~UI_Thread();

      void run(std::shared_ptr<abstractions::ui::AWindow> x_window) noexcept;
  };
}
