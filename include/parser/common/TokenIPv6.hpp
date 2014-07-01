#if !defined(SIP0X_PARSER_TOKENIPV6_HPP__)
#define SIP0X_PARSER_TOKENIPV6_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"

#include <cstdint>

namespace Sip0x
{
  namespace Parser
  {
    class TokenIPv6 : public TokenAbstract {

    protected:
      TokenRegex _regex;

    public:
      TokenIPv6(void) : TokenAbstract(), _regex("\\b((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}\\b") {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenIPv6");
      }

      virtual ~TokenIPv6(void) {
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        // TODO: Implements ...
        ReadResult result; // = _regex.read(iss);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENIPV6_HPP__
