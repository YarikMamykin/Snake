#ifndef SRC_INCLUDE_COMMANDS_QUERYTEXTHEIGHT_HPP
#define SRC_INCLUDE_COMMANDS_QUERYTEXTHEIGHT_HPP

#include "Command.hpp"
#include <string>

namespace commands {

  class QueryTextHeight : public Command {
    protected:
      unsigned int height;

    public:
      explicit QueryTextHeight() = default;
      ~QueryTextHeight() override = default;

      virtual DoSaveResult execute() override;
      virtual constexpr CommandID get_id() const override;
      const unsigned int get_height() const;
  };
}


#endif /* SRC_INCLUDE_COMMANDS_QUERYTEXTHEIGHT_HPP */
