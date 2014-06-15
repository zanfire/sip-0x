#if !defined(SIP0X_PARSER_ALTERNATIVE_HPP__)
#define SIP0X_PARSER_ALTERNATIVE_HPP__

#include <string>
#include <vector>
#include <memory>
#include <tuple>


#include "parser/base/OpAbstract.hpp"

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

      void add(std::shared_ptr<TokenAbstract> op) {
        DEBUG(_logger, "Adding alternative %s.", op->name());
        _alternatives.push_back(op);
      }


      virtual ReadResult handle_read(std::istringstream& iss) override {
        for (auto op : _alternatives) {
          ReadResult result = op->read(iss);
          if (result.successes) {
            DEBUG(_logger, "Alternative %s successes.", op->name());
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
