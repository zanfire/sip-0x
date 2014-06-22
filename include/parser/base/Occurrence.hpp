#if !defined(SIP0X_PARSER_OCCURRENCE_HPP__)
#define SIP0X_PARSER_OCCURRENCE_HPP__

#include "parser/base/OpAbstract.hpp"

namespace Sip0x
{
  namespace Parser
  {
    template<class T>
    class Occurrence : public OpAbstract {
    protected:
      T _token;
      int _min;
      int _max;

    public:
      Occurrence(T& f, int min = 0, int max = -1) : OpAbstract(), _token(f), _min(min), _max(max) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.OpOccurrence");
      }

      virtual ~Occurrence(void) {
        DEBUG(_logger, "Destroying OpOccurrence@%p.", this);
      }

      virtual void set_parent(TokenAbstract* parent) override {
        _parent = parent;
        _token.set_parent(parent);
        // for each 
      }

    protected:
   
      virtual ReadResult handle_read(std::istringstream& iss, void* ctx) const override {
        
        int occurrence = 0;
        ReadResult output(false);
        while ((_max >= 0 && occurrence <= _max) || _max == -1) {
          output = _token.read(iss, ctx);

          if (!output.successes) {
            break;
          }
          occurrence++;
        }

        if (occurrence >= _min && (occurrence <= _max || _max == -1)) {
          DEBUG(_logger, "Successes Occurrence@%p, occurrence: %d in range [%d - %d].", this, occurrence, _min, _max);
          // TODO: Accumulate resulting object returned by each occurrence.
          return ReadResult(true);
        }
        else {
          DEBUG(_logger, "Failed Occurrence@%p, occurrence: %d out of range [%d - %d].", this, occurrence, _min, _max);
          return output;
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_OCCURRENCE_HPP__
