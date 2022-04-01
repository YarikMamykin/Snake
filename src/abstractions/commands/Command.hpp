#ifndef SRC_INCLUDE_COMMANDS_COMMAND_HPP
#define SRC_INCLUDE_COMMANDS_COMMAND_HPP
#include <list>
#include <memory>
#include <mutex>
#include <xlib/XProxy/XProxy.hpp>

namespace commands {

  class Command {
    public:
      virtual void execute(xlib::XProxy&) = 0;
      virtual ~Command() = default;
      
    private:
      static std::mutex xlib_queue_mutex;
      static std::list<std::unique_ptr<Command>> commands_to_xlib_queue;

    public:
      static void push_xlib_command(std::unique_ptr<Command> command);
      static std::unique_ptr<Command> pop_xlib_command();
      static bool xlib_queue_empty();
  };
}



#endif /* SRC_INCLUDE_COMMANDS_COMMAND_HPP */
