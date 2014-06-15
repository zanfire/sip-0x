#if !defined(SIP0X_PARSER_OPSEQUENCE_HPP__)
#define SIP0X_PARSER_OPSEQUENCE_HPP__

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "parser/base/OpAbstract.hpp"
#include "parser/base/OpOccurrence.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"
#include "utils/log/LoggerManager.hpp"

namespace Sip0x
{
  namespace Parser
  {
    class OpSequence : public OpAbstract {

    protected:
      std::vector<std::shared_ptr<TokenAbstract>> _sequence;


    public:
      OpSequence(void) : OpAbstract() {
        _logger = LoggerManager::get_logger("Sip0x.Parser.OpSequence");
      }

      virtual ~OpSequence(void) {}

      void add(std::shared_ptr<TokenAbstract> op) {
        _sequence.push_back(op);
      }

      void add_token(std::string token) {
        std::shared_ptr<TokenAbstract> t(new Token(token));
        add(t);
      }

      void add_regex(std::string regex) {
        std::shared_ptr<TokenAbstract> t;
        t.reset(new TokenRegex(regex));
        add(t);
      }

      void add_occurrence(std::shared_ptr<TokenAbstract> t, int min, int max) {
        std::shared_ptr<TokenAbstract> el(new OpOccurrence(t, min, max));
        add(el);
      }


      virtual ReadResult handle_read(std::istringstream& iss) override {
        // TODO: Improves 
        for (auto op : _sequence) {
          ReadResult result = op->read(iss);

          if (!result.successes) {
            return ReadResult(false);
          }
        }
        return ReadResult(true);
      }
    };
  }
}

#endif // SIP0X_PARSER_OPSEQUENCE_HPP__
