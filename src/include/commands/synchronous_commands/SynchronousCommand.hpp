#ifndef SRC_INCLUDE_COMMANDS_SYNCHRONOUS_COMMAND_SYNCHRONOUSCOMMAND_HPP
#define SRC_INCLUDE_COMMANDS_SYNCHRONOUS_COMMAND_SYNCHRONOUSCOMMAND_HPP

#include "Command.hpp" 
#include <atomic>

namespace commands {

  class SynchronousCommand : public Command {
    protected:
      std::atomic<bool>& trigger;

      explicit SynchronousCommand(std::atomic<bool>& trigger) 
      : trigger(trigger) { }

    public:
      virtual ~SynchronousCommand() override = default;
  };
}



#endif /* SRC_INCLUDE_COMMANDS_SYNCHRONOUS_COMMAND_SYNCHRONOUSCOMMAND_HPP */
