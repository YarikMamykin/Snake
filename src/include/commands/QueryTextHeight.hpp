#ifndef SRC_INCLUDE_COMMANDS_QUERYTEXTHEIGHT_HPP
#define SRC_INCLUDE_COMMANDS_QUERYTEXTHEIGHT_HPP

#include "Command.hpp"
#include <string>

namespace commands {

  class QueryTextHeight : public SynchronousCommand {
    protected:
      unsigned int& height;

    public:
      explicit QueryTextHeight(unsigned int& result, std::atomic<bool>& trigger);
      ~QueryTextHeight() override = default;

      virtual DoSaveResult execute() override;
      virtual constexpr CommandID get_id() const override;
  };
}


#endif /* SRC_INCLUDE_COMMANDS_QUERYTEXTHEIGHT_HPP */
