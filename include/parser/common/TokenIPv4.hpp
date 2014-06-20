#if !defined(SIP0X_PARSER_TOKENIPv4_HPP__)
#define SIP0X_PARSER_TOKENIPv4_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"

#include <cstdint>

namespace Sip0x
{
  namespace Parser
  {
    class TokenIPv4 : public TokenAbstract {

    protected:
      TokenRegex _regex;

    public:
      TokenIPv4(void) : TokenAbstract(), _regex("\\b((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}\\b") {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenIPv4");
      }

      virtual ~TokenIPv4(void) {
      }

    protected:
      virtual ReadResult handle_read(std::istringstream& iss) const override {
        //
        ReadResult result = _regex.read(iss);

        if (result.successes) {
          std::stringstream s(result.parsed);
          int oct1, oct2, oct3, oct4;
          char dot;
          s >> oct1 >> dot >> oct2 >> dot >> oct3 >> dot >> oct4;
          uint32_t* ipv4 = new uint32_t;
          *ipv4 = (oct1 << 24 | oct2 << 16 | oct3 << 8 | oct4);
          result.result = ipv4;
          result.result_dtor = [](void* p) { 
            int* ptr = (int*)p; delete ptr; 
          };
        }

        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENIPV4_HPP__
