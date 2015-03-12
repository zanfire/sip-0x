#if !defined(SIP0X_PARSER_TOKENGENERICPARAM_HPP__)
#define SIP0X_PARSER_TOKENGENERICPARAM_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"
#include "parser/base/Operators.hpp"

#include "parser/common/TokenHostport.hpp"
#include "parser/common/TokenQuotedString.hpp"

namespace sip0x
{
  namespace Parser
  {
    // generic-param  =  token [ EQUAL gen-value ]
    // gen-value      =  token / host / quoted-string
    class TokenGenericParam : public TokenAbstract {

    protected:
      Sequence<TokenRegex, TokenEQUAL, Alternative<TokenRegex, TokenHost, TokenQuotedString>> _sequence;

    public:
      TokenGenericParam(void) : TokenAbstract("TokenGenericParam"), 
        _sequence(
          TokenRegex(RegexConstStrings::token),
          TokenEQUAL(),
          Alternative<TokenRegex, TokenHost, TokenQuotedString>(
            TokenRegex(RegexConstStrings::token),
            TokenHost(),
            TokenQuotedString()
          )
        ) {
      }

    protected:
      virtual ReadResult handle_read(sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ReadResult result = _sequence.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENGENERICPARAM_HPP__
