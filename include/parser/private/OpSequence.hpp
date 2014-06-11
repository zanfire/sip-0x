#if !defined(SIP0X_PARSER_OPSEQUENCE_HPP__)
#define SIP0X_PARSER_OPSEQUENCE_HPP__

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "parser/private/OpAbstract.hpp"
#include "utils/log/LoggerManager.hpp"

namespace Sip0x
{
  namespace Parser
  {
    class OpSequence : public OpAbstract {

    protected:
      std::vector<std::shared_ptr<OpAbstract>> _sequence;


    public:
      OpSequence(void) : OpAbstract() {
        _logger = LoggerManager::get_logger("Sip0x.Parser.OpSequence");

      }

      virtual ~OpSequence(void) {}

      void add(std::shared_ptr<OpAbstract> op) {
        _sequence.push_back(op);
      }


      virtual std::tuple<bool, void*>  parse(std::istringstream& iss) override {
        /*for (auto op : _alternatives) {
          //std::tuple<bool, void*> result = rule->parse(iss);
          std::tuple<bool, void*> result = op->parse(iss);

          if (std::get<0>(result)) {
            return result;
          }
        }
        */
        return std::tuple<bool, void*>(false, nullptr);
      }
    };
  }
}

#endif // SIP0X_PARSER_OPSEQUENCE_HPP__
