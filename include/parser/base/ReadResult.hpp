#if !defined(SIP0X_PARSER_READRESULT_HPP__)
#define SIP0X_PARSER_READRESULT_HPP__

#include <tuple>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"

namespace Sip0x
{
  namespace Parser
  {
    using namespace Sip0x::Utils::Log;

    struct ReadResult {
      bool successes;
      std::string parsed;
      // Error position.
      std::streamoff errorpos;
      std::string errormessage;

      ReadResult(void) : successes(false), parsed(), errorpos(-2) {}
      ReadResult(bool s) : successes(s), parsed(), errorpos(-2) {}
      ReadResult(bool s, std::string str) : successes(s), parsed(str), errorpos(-2) {}
      ReadResult(bool s, std::string str, void* r) : successes(s), parsed(str), errorpos(-2) {}

      void set_error(std::streamoff pos, std::string message) {
        errorpos = pos;
        errormessage = message;
      }
    };
  }
}

#endif // SIP0X_PARSER_READRESULT_HPP__
