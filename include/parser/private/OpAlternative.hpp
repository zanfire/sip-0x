#if !defined(SIP0X_PARSER_ALTERNATIVE_HPP__)
#define SIP0X_PARSER_ALTERNATIVE_HPP__

#include <string>
#include <vector>
#include <memory>
#include <tuple>


#include "parser/private/OpAbstract.hpp"

namespace Sip0x
{
  namespace Parser
  {
    /// This parser expects a specific token and return an instance. 
    class OpAlternative : public OpAbstract {

    protected:
      std::vector<std::shared_ptr<OpAbstract>> _alternatives;
      

    public:
      OpAlternative(void) : OpAbstract() {
      }

      virtual ~OpAlternative(void) {}

      void add(std::shared_ptr<OpAbstract> op) {
        _alternatives.push_back(op);
      }


      virtual std::tuple<bool, void*> handle_read(std::istringstream& iss) override {
        for (auto op : _alternatives) {
          std::tuple<bool, void*> result = op->parse(iss);
          if (std::get<0>(result)) {
            return result;
          }
        }
        return std::tuple<bool, void*>(false, nullptr);
      }
    };
  }
}

#endif // SIP0X_PARSER_ALTERNATIVE_HPP__
