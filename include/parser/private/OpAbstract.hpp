#if !defined(SIP0X_PARSER_OPABSTRACT_HPP__)
#define SIP0X_PARSER_OPABSTRACT_HPP__

#include <algorithm>
#include <memory>

#include "utils/log/Logger.hpp"

namespace Sip0x
{
  namespace Parser
  {
    using namespace Utils::Log;

    class OpAbstract {
    protected:
      std::shared_ptr<Logger> _logger;

    public:
      OpAbstract(void) {}

      virtual ~OpAbstract(void) {}

      virtual std::tuple<bool, void*>  parse(std::istringstream& iss) = 0;
    };
  }
}

#endif // SIP0X_PARSER_OPABSTRACT_HPP__
