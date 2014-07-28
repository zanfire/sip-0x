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
      // "\\b((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}\\b"  \\b((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}\\b
      // [0-9]{3}.[0-9]{3}.[0-9]{3}.[0-9]{3}
      TokenIPv4(void) : TokenAbstract("ipv4"), _regex("ipv4", "[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}") {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenIPv4");
      }

      virtual ~TokenIPv4(void) {
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        //
        ReadResult result = _regex.read(iss, ctx);

        if (result.successes) {
          std::stringstream s(result.parsed);
          int oct1, oct2, oct3, oct4;
          char dot;
          s >> oct1 >> dot >> oct2 >> dot >> oct3 >> dot >> oct4;
          
          if (oct1 > 255 || oct2 > 255 || oct3 > 255 || oct4 > 255) {
            DEBUG(_logger, "IPv4 out of range.");
            result.successes = false;
            result.parsed = "";
            return result;
          }

          //uint32_t* ipv4 = new uint32_t;
          //*ipv4 = (oct1 << 24 | oct2 << 16 | oct3 << 8 | oct4);
        }

        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENIPV4_HPP__
