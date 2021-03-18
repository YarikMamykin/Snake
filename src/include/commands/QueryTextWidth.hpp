#ifndef SRC_INCLUDE_COMMANDS_QUERYTEXTWIDTH_HPP
#define SRC_INCLUDE_COMMANDS_QUERYTEXTWIDTH_HPP

#include "Command.hpp"
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

      virtual DoSaveResult execute() override;
      virtual constexpr CommandID get_id() const override;
  };
}

#endif /* SRC_INCLUDE_COMMANDS_QUERYTEXTWIDTH_HPP */
