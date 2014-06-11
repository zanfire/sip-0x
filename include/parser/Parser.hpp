#if !defined(SIP0X_PARSER_PARSER_HPP__)
#define SIP0X_PARSER_PARSER_HPP__

#include <tuple>
#include <vector>
#include <sstream>
#include <iostream>
#include <memory>

#include "parser/private/OpAbstract.hpp"

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
      std::shared_ptr<OpAbstract> _root;

    public:
      Parser(std::shared_ptr<OpAbstract>& root) : _root(root) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.Parser");
      }

      virtual ~Parser(void) {}


      bool parse(std::string& text) {
        DEBUG(_logger, "Parsing string \"%s\".", text.c_str());

        std::istringstream iss(text);
        std::tuple<bool, void*> result = _root->parse(iss);

        if (!std::get<0>(result)) {
          DEBUG(_logger, "Parsing failed.", text.c_str());
          return false;
        }
        DEBUG(_logger, "Parsing successes.", text.c_str());
        return true;
      }
    };
  }
}

#endif // SIP0X_PARSER_PARSER_HPP__
