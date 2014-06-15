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
      void* result;
      std::function<void(void*)> result_dtor;

      ReadResult(void) : successes(false), parsed(), result(nullptr) {}
      ReadResult(bool s) : successes(s), parsed(), result(nullptr) {}
      ReadResult(bool s, std::string str) : successes(s), parsed(str), result(nullptr) {}
      ReadResult(bool s, std::string str, void* r) : successes(s), parsed(str), result(r) {}

      void dispose() {
        if (result != nullptr) {
          result_dtor(result);
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_READRESULT_HPP__
