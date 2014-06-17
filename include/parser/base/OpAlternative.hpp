#if !defined(SIP0X_PARSER_ALTERNATIVE_HPP__)
#define SIP0X_PARSER_ALTERNATIVE_HPP__

#include <string>
#include <vector>
#include <memory>
#include <tuple>


#include "parser/base/OpAbstract.hpp"
#include "parser/base/OpOccurrence.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"

namespace Sip0x
{
  namespace Parser
  {
    /// This parser expects a specific token and return an instance. 
    class OpAlternative : public OpAbstract {

    protected:
      std::vector<std::shared_ptr<TokenAbstract>> _alternatives;
      
    public:
      OpAlternative(void) : OpAbstract() {
        _logger = LoggerManager::get_logger("Sip0x.Parser.OpAlternative");
        DEBUG(_logger, "Creating OpAlternative@%p.", this);
      }

      virtual ~OpAlternative(void) {
        DEBUG(_logger, "Destroying OpAlternative@%p.", this);
      }

      void add_token(std::string token) {
        std::shared_ptr<TokenAbstract> t(new Token(token));
        add(token, t);
      }

      void add_regex(std::string name, std::string regex) {
        std::shared_ptr<TokenAbstract> t;
        t.reset(new TokenRegex(regex));
        add(name, t);
      }

      void add(std::string name, std::shared_ptr<TokenAbstract> op) {
        op->set_name(name);
        add(op);
      }

      void add(std::shared_ptr<TokenAbstract> op) {
        DEBUG(_logger, "Adding alternative %s.", op->get_name());
        _alternatives.push_back(op);
      }


      virtual ReadResult handle_read(std::istringstream& iss) override {
        for (auto op : _alternatives) {
          ReadResult result = op->read(iss);
          if (result.successes) {
            DEBUG(_logger, "Alternative %s successes.", op->get_name());
            return result;
          }
        }
        DEBUG(_logger, "No alternative parsed correctly.");
        return ReadResult(false);
      }
    };
  }
}

#endif // SIP0X_PARSER_ALTERNATIVE_HPP__
