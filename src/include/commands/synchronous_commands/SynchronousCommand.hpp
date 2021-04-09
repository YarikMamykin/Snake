#ifndef SRC_INCLUDE_COMMANDS_SYNCHRONOUS_COMMANDS_SYNCHRONOUSCOMMAND_HPP
#define SRC_INCLUDE_COMMANDS_SYNCHRONOUS_COMMANDS_SYNCHRONOUSCOMMAND_HPP

#include "commands/Command.hpp" 
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




#endif /* SRC_INCLUDE_COMMANDS_SYNCHRONOUS_COMMANDS_SYNCHRONOUSCOMMAND_HPP */
