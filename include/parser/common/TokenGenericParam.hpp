#if !defined(SIP0X_PARSER_TOKENGENERICPARAM_HPP__)
#define SIP0X_PARSER_TOKENGENERICPARAM_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"
#include "parser/base/Operators.hpp"

#include "parser/common/TokenHostport.hpp"
#include "parser/common/TokenQuotedString.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // generic-param  =  token [ EQUAL gen-value ]
    // gen-value      =  token / host / quoted-string
    class TokenGenericParam : public TokenAbstract {

    protected:
      Sequence<TokenRegex, Token, Alternative<TokenRegex, TokenHost, TokenQuotedString>> _sequence;

    public:
      TokenGenericParam(void) : TokenAbstract("TokenGenericParam"), 
        _sequence(
          TokenRegex(RegexConstStrings::token),
          Token("="),
          Alternative<TokenRegex, TokenHost, TokenQuotedString>(
            TokenRegex(RegexConstStrings::token),
            TokenHost(),
            TokenQuotedString()
          )
        ) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenGenericParam");
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult result = _sequence.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENGENERICPARAM_HPP__
