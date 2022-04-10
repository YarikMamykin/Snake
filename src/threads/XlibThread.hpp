#pragma once 

#include <functional>
#include <list>
#include <future>

namespace std {
  class mutex;
}

namespace abstractions::ui {
  class AWindow;
}

namespace threads {
  class XlibThread { 

    private:
      std::future<void> m_handler;

    public:
      explicit XlibThread();
      ~XlibThread();

      bool init() const noexcept;

      void run(std::shared_ptr<abstractions::ui::AWindow> x_window) noexcept;
  };
}

