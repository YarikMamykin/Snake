#include "Command.hpp"
#include <thread>
#include <iostream>

namespace commands {

  std::mutex Command::xlib_queue_mutex;
  std::list<std::unique_ptr<Command>> Command::commands_to_xlib_queue;

  void Command::push_xlib_command(std::unique_ptr<Command> command) {
    std::lock_guard<std::mutex> xlib_guard(xlib_queue_mutex);
    commands_to_xlib_queue.emplace_back(std::move(command));
  }

  void Command::push_xlib_command(Command* command) {
    std::lock_guard<std::mutex> xlib_guard(xlib_queue_mutex);
    commands_to_xlib_queue.emplace_back(command);
  }

  std::unique_ptr<Command> Command::pop_xlib_command() {
    std::lock_guard<std::mutex> xlib_guard(xlib_queue_mutex);
    std::unique_ptr<Command> command = std::move(commands_to_xlib_queue.front());
    commands_to_xlib_queue.pop_front();
    return command;
  }

  bool Command::xlib_queue_empty() {
    std::lock_guard<std::mutex> xlib_guard(xlib_queue_mutex);
    return commands_to_xlib_queue.empty();
  }
}
