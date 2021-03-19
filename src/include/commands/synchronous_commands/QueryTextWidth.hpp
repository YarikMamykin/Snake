#ifndef SRC_INCLUDE_COMMANDS_QUERYTEXTWIDTH_HPP
#define SRC_INCLUDE_COMMANDS_QUERYTEXTWIDTH_HPP

#include "SynchronousCommand.hpp"
#include <string>

namespace commands {

  class QueryTextWidth : public SynchronousCommand {
    protected:
      const std::string text;
      unsigned int& width;

    public:
      explicit QueryTextWidth(const std::string& text, 
                              unsigned int& result,
                              std::atomic<bool>& trigger);
      ~QueryTextWidth() override = default;

      virtual void execute() override;
  };
}

#endif /* SRC_INCLUDE_COMMANDS_QUERYTEXTWIDTH_HPP */
