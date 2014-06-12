#if !defined(SIP0X_PARSER_PARSERABSTRACT_HPP__)
#define SIP0X_PARSER_PARSERABSTRACT_HPP__

#include <tuple>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"

namespace Sip0x
{
  namespace Parser
  {
    using namespace Sip0x::Utils::Log;

    class TokenAbstract {

    protected:
      std::shared_ptr<Logger> _logger;

    public:
      TokenAbstract() {
      }

      virtual ~TokenAbstract(void) {}

      // Read the expected token.
      // returns true if encountered the expected token.  
      virtual std::tuple<bool, void*>  read(std::istringstream& iss) sealed {
        if (iss.eof()) {
          DEBUG(_logger, "Stream is empty, skipping...");
          return std::tuple<bool, void*>(false, nullptr);
        }

        std::streamoff initial_pos = iss.tellg();
        
        DEBUG(_logger, "Saved position %lld during parsing.", (long long)initial_pos);
        
        std::tuple<bool, void*> result = handle_read(iss);

        if (std::get<0>(result)) {
          // TODO: avoid this consumption ... 
          long long delta = (long long)((iss.eof() ? iss.str().length() : iss.tellg()) - initial_pos);
          DEBUG(_logger, "Consumed chars %lld during parsing.", delta);
        }
        else {
          iss.seekg(initial_pos);
          DEBUG(_logger, "Restored position %lld during parsing.", (long long)initial_pos);
        }
        return result;
      }

      virtual char const* name(void) { return typeid(this).name(); }


    protected:
      virtual std::tuple<bool, void*>  handle_read(std::istringstream& iss) = 0;
    };
  }
}

#endif // SIP0X_PARSER_PARSERABSTRACT_HPP__
