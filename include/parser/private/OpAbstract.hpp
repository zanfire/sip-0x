#if !defined(SIP0X_PARSER_OPABSTRACT_HPP__)
#define SIP0X_PARSER_OPABSTRACT_HPP__

#include <algorithm>
#include <memory>


#include "parser/private/TokenAbstract.hpp"
#include "utils/log/Logger.hpp"

namespace Sip0x
{
  namespace Parser
  {
    using namespace Utils::Log;

    class OpAbstract : public TokenAbstract {
    protected:
      
    public:
      OpAbstract(void) {}

      virtual ~OpAbstract(void) {}

      virtual std::tuple<bool, void*>  parse(std::istringstream& iss) sealed {
        return read(iss);
      }

    protected:
      
    };
  }
}

#endif // SIP0X_PARSER_OPABSTRACT_HPP__
