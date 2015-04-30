#if !defined(SIP0X_PARSER_TOKENGENERICPARAM_HPP__)
#define SIP0X_PARSER_TOKENGENERICPARAM_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Token.hpp"
#include "parser/tokens/TokenRegex.hpp"
#include "parser/tokens/Operators.hpp"

#include "parser/tokens/TokenHostport.hpp"
#include "parser/tokens/TokenQuotedString.hpp"

namespace sip0x
{
  namespace parser
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
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ParserResult result = _sequence.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENGENERICPARAM_HPP__
