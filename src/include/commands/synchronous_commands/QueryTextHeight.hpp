#ifndef SRC_INCLUDE_COMMANDS_QUERYTEXTHEIGHT_HPP
#define SRC_INCLUDE_COMMANDS_QUERYTEXTHEIGHT_HPP

#include "SynchronousCommand.hpp"
#include <string>

namespace commands {

  class QueryTextHeight : public SynchronousCommand {
    protected:
      unsigned int& height;

    public:
      explicit QueryTextHeight(unsigned int& result, std::atomic<bool>& trigger);
      ~QueryTextHeight() override = default;

      virtual void execute() override;
  };
}


#endif /* SRC_INCLUDE_COMMANDS_QUERYTEXTHEIGHT_HPP */
