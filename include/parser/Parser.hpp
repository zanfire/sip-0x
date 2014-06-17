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
      std::ostringstream _readable_error;
      std::shared_ptr<Logger> _logger;
      // Collections of rules.
      std::shared_ptr<TokenAbstract> _root;

    public:
      Parser(std::shared_ptr<TokenAbstract>& root) : _root(root) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.Parser");
      }

      virtual ~Parser(void) {}


      bool parse(std::string& text) {
        _readable_error.clear();
        _readable_error.str("");
        DEBUG(_logger, "Parsing string \"%s\".", text.c_str());

        std::istringstream iss(text);
        ReadResult result = _root->read(iss);

        if (result.successes && (iss.eof() || ((long long)iss.tellg() == (long long)text.length()))) {
          DEBUG(_logger, "Parsing successes, stream: %lld, gcount: %lld, tellg %lld.", (long long)iss.eof(), (long long)iss.gcount(), (long long)iss.tellg());

          if (result.result != nullptr) {
            result.result_dtor(result.result);
          }
          return true;
        }
        else {
          std::streampos cur_pos = iss.tellg();
          std::string r;
          iss >> r;

          if (result.errorpos == -2) {
            result.set_error(cur_pos, "Remaining string: " + r);
          }

          _readable_error << "Parsing error (pos: ";
          if (result.errorpos == -1) {
            _readable_error << "eof";
          }
          else {
            _readable_error << result.errorpos;
          }
          _readable_error << ") message: " << result.errormessage;


          DEBUG(_logger, "Parsing terminated without successes, remaining string: %s.", r.c_str());
          return false;
        }
      }

      std::string get_readable_error() { return _readable_error.str(); }
    };
  }
}

#endif // SIP0X_PARSER_PARSER_HPP__
