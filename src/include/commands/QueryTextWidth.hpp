#ifndef SRC_INCLUDE_COMMANDS_QUERYTEXTWIDTH_HPP
#define SRC_INCLUDE_COMMANDS_QUERYTEXTWIDTH_HPP

#include "Command.hpp"
#include <string>

namespace commands {

  class QueryTextWidth : public Command {
    protected:
      unsigned int width;
      const std::string text;

    public:
      explicit QueryTextWidth(const std::string& text);
      ~QueryTextWidth() override = default;

      virtual DoSaveResult execute() override;
      virtual constexpr CommandID get_id() const override;
      const unsigned int get_width() const;
  };
}

#endif /* SRC_INCLUDE_COMMANDS_QUERYTEXTWIDTH_HPP */
