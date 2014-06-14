#if !defined(SIP0X_PARSER_PARSERABSTRACT_HPP__)
#define SIP0X_PARSER_PARSERABSTRACT_HPP__

#include <tuple>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "parser/base/ReadResult.hpp"

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


      // Returns a tuple with:
      //  0: result (true or false)
      //  1: parsed string.
      //  1: unique pointer to an allocated object.
      virtual ReadResult  read(std::istringstream& iss) sealed {
        ReadResult output;
        
        if (iss.eof()) {
          DEBUG(_logger, "Stream is empty, skipping...");
          return output;
        }

        std::streamoff initial_pos = iss.tellg();
        
        DEBUG(_logger, "Saved position %lld during parsing.", (long long)initial_pos);
        
        ReadResult result = handle_read(iss);

        if (result.successes) {
          std::string str = iss.str();
          // TODO: avoid this consumption ... 
          long long delta = (long long)((iss.eof() ? str.length() : iss.tellg()) - initial_pos);
          std::string parsed = str.substr((unsigned int)initial_pos, (unsigned int)delta);
          DEBUG(_logger, "Consumed chars %lld during parsing, parsed %s.", delta, parsed.c_str());

          output = result;
          output.parsed = parsed;
        }
        else {
          iss.seekg(initial_pos);
          DEBUG(_logger, "Restored position %lld during parsing.", (long long)initial_pos);
        }
        return output;
      }

      virtual char const* name(void) { return typeid(this).name(); }

      // Returns a tuple with:
      //  0: result (true or false)
      //  1: unique pointer to an allocated object.
      virtual ReadResult  handle_read(std::istringstream& iss) = 0;
    };
  }
}

#endif // SIP0X_PARSER_PARSERABSTRACT_HPP__