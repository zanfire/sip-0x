#if !defined(SIP0X_PARSER_OPOCCURRENCE_HPP__)
#define SIP0X_PARSER_OPOCCURRENCE_HPP__

#include <string>
#include <vector>
#include <memory>

#include "parser/base/OpAbstract.hpp"
#include "parser/base/TokenAbstract.hpp"

#include "utils/log/LoggerManager.hpp"


namespace Sip0x
{
  namespace Parser
  {
    class OpOccurrence : public OpAbstract {

    protected:
      std::shared_ptr<TokenAbstract> _token;
      int _min;
      int _max;

    public:
      OpOccurrence(std::shared_ptr<TokenAbstract> token, int min, int max) : OpAbstract() {
        _logger = LoggerManager::get_logger("Sip0x.Parser.OpOccurrence");

        _token = token;
        _min = min;
        _max = max;

        DEBUG(_logger, "Creating OpOccurrence@%p for token %s range [%d, %d].", this, token->name(), _min, _max);
      }

      virtual ~OpOccurrence(void) {
        DEBUG(_logger, "Destroying OpOccurrence@%p.", this);
      }


      virtual ReadResult handle_read(std::istringstream& iss) override {
        int occurrence = 0;
        while ((_max >= 0 && occurrence <= _max) || _max == -1) {
          ReadResult result = _token->handle_read(iss);

          if (!result.successes) {
            break;
          }
          occurrence++;
        }

        if (occurrence >= _min && (occurrence <= _max || _max == -1)) {
          DEBUG(_logger, "Successes OpOccurrence@%p, occurrence: %d in range [%d - %d].", this, occurrence, _min, _max);
          // TODO: Accumulate resulting object returned by each occurrence.
          return ReadResult(true);
        }
        else {
          DEBUG(_logger, "Failed OpOccurrence@%p, occurrence: %d out of range [%d - %d].", this, occurrence, _min, _max);
          return ReadResult(false);
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_OPOCCURRENCE_HPP__