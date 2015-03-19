#if !defined(SIP0X_PARSER_TOKENIPv4_HPP__)
#define SIP0X_PARSER_TOKENIPv4_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Token.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include <cstdint>
#include <sstream>

namespace sip0x
{
  namespace parser
  {
    class TokenIPv4 : public TokenAbstract {

    protected:
      TokenRegex _regex;

    public:
      // "\\b((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}\\b"  \\b((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}\\b
      // [0-9]{3}.[0-9]{3}.[0-9]{3}.[0-9]{3}
      TokenIPv4(void) : TokenAbstract("ipv4"), _regex("ipv4", "[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}") {
      }

      virtual ~TokenIPv4(void) {
      }

    protected:
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        //
        ParserResult result = _regex.read(iss, ctx);

        if (result.success()) {
          std::stringstream s(iss.str(result.position(), result.length()));
          int oct1, oct2, oct3, oct4;
          char dot;
          s >> oct1 >> dot >> oct2 >> dot >> oct3 >> dot >> oct4;
          
          if (oct1 > 255 || oct2 > 255 || oct3 > 255 || oct4 > 255) {
            result.push_event(ParserResult::TYPE_ERROR, result.position(), "Content is not a valid IPv4.");
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
