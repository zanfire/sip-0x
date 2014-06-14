#if !defined(SIP0X_PARSER_OPABSTRACT_HPP__)
#define SIP0X_PARSER_OPABSTRACT_HPP__

#include <algorithm>
#include <memory>


#include "parser/base/TokenAbstract.hpp"
#include "utils/log/Logger.hpp"

namespace Sip0x
{
  namespace Parser
  {
    
    class OpAbstract : public TokenAbstract {
    public:
      OpAbstract(void) {}

      virtual ~OpAbstract(void) {}

      virtual ReadResult parse(std::istringstream& iss) sealed {
        return read(iss);
      }

    protected:
      
    };
  }
}

#endif // SIP0X_PARSER_OPABSTRACT_HPP__
