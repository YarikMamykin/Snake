#ifndef SRC_INCLUDE_COMMANDS_COMMAND_HPP
#define SRC_INCLUDE_COMMANDS_COMMAND_HPP

#include "Rectangle.hpp" 
#include "Color.hpp"
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <atomic>

namespace commands {
  enum class CommandID : unsigned char {
    DrawCircle,
    DrawRectangle,
    DrawText,
    FillCircle,
    FillRectangle,
    QueryTextWidth,
    QueryTextHeight,
    ChangeView,
    QueryWindowAttributes,
    ExitApplication
  };

  enum DoSaveResult {
    YES = true,
    NO = false
  };

  class Command {
    public:
      virtual DoSaveResult execute() = 0;
      virtual constexpr CommandID get_id() const = 0;
      virtual ~Command() = default;
      
    private:
      static std::mutex xlib_queue_mutex;
      static std::mutex results_mutex;
      static std::atomic<bool> may_watch_result;

      static std::list<std::unique_ptr<Command>> commands_to_xlib_queue;
      static std::map<CommandID, std::unique_ptr<Command>> commands_results;

    public:
      static void push_xlib_command(std::unique_ptr<Command> command);
      static void push_xlib_command(Command* command);
      static std::unique_ptr<Command> pop_xlib_command();
      static bool xlib_queue_empty();
      static bool results_queue_empty();
      static void put_command_with_result(std::unique_ptr<Command> command);
      static std::unique_ptr<Command> get_command_with_result(CommandID&& cid);
  };

  class GraphicsCommand : public Command {
    protected:
      geometry::Rectangle rectangle;
      color::Color color;

      explicit GraphicsCommand (const geometry::Rectangle& rectangle, const color::Color& color) 
      : rectangle(rectangle), color(color) { }
    public: 
      virtual ~GraphicsCommand() override = default;

  };
}


#endif /* SRC_INCLUDE_COMMANDS_COMMAND_HPP */
