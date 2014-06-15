#if !defined(SIP0X_PARSER_PARSER_HPP__)
#define SIP0X_PARSER_PARSER_HPP__

#include <tuple>
#include <vector>
#include <sstream>
#include <iostream>
#include <memory>

#include "parser/base/OpAbstract.hpp"

#include "utils/log/Logger.hpp"
#include "utils/log/LoggerManager.hpp"

namespace Sip0x
{
  namespace Parser
  {
    using namespace Sip0x::Utils::Log;

    class Parser {

    protected:
      std::shared_ptr<Logger> _logger;
      // Collections of rules.
      std::shared_ptr<TokenAbstract> _root;

    public:
      Parser(std::shared_ptr<TokenAbstract>& root) : _root(root) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.Parser");
      }

      virtual ~Parser(void) {}


      bool parse(std::string& text) {
        DEBUG(_logger, "Parsing string \"%s\".", text.c_str());

        std::istringstream iss(text);
        ReadResult result = _root->read(iss);

        if (result.successes && (iss.eof() || iss.gcount() == 0)) {
          DEBUG(_logger, "Parsing successes.");

          if (result.result != nullptr) {
            result.result_dtor(result.result);
          }
          return true;
        }
        else {
          std::string r;
          iss >> r;
          DEBUG(_logger, "Parsing terminated without successes, remaining string: %s.", r.c_str());
          return false;
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_PARSER_HPP__
