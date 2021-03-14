#include "Command.hpp"
#include <thread>
#include <iostream>

namespace commands {

  std::mutex Command::xlib_queue_mutex;
  std::mutex Command::results_mutex;

  std::atomic<bool> Command::may_watch_result(false);

  std::list<std::unique_ptr<Command>> Command::commands_to_xlib_queue;
  std::map<CommandID, std::unique_ptr<Command>> Command::commands_results;

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
    return commands_to_xlib_queue.empty();
  }

  bool Command::results_queue_empty() {
    return commands_results.empty();
  }

  void Command::put_command_with_result(std::unique_ptr<Command> command) {
    commands_results[command->get_id()] = std::move(command);
  }

  std::unique_ptr<Command> Command::get_command_with_result(CommandID&& cid) {
    auto result_it = commands_results.end();
    // TODO: REFACTOR NEXT 2 LINES!
    while((result_it = commands_results.find(cid)) == commands_results.end());
    while(!result_it->second);
    std::unique_ptr<Command> command_with_result = std::move(result_it->second);
    commands_results.erase(result_it);
    return command_with_result;
  }
}
