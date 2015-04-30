#if !defined(SIP0X_PARSER_TOKENQUOTEDSTRING_HPP__)
#define SIP0X_PARSER_TOKENQUOTEDSTRING_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Token.hpp"
#include "parser/tokens/TokenRegex.hpp"
#include "parser/tokens/Operators.hpp"

#include "parser/tokens/RegexConstStrings.hpp"

namespace sip0x
{
  namespace parser
  {
    // quoted-string  =  SWS DQUOTE *(qdtext / quoted-pair) DQUOTE
    // qdtext         =  LWS / %x21 / %x23-5B / %x5D-7E / UTF8-NONASCII
    // quoted-pair  =  "\" (%x00-09 / %x0B-0C / %x0E-7F)
    class TokenQuotedString : public TokenAbstract {

    protected:
      Sequence<TokenRegex, Token, TokenRegex, Token> _sequence;

    public:
      TokenQuotedString(void) : TokenAbstract("TokenQuotedString"), 
        _sequence(
          TokenRegex("SWS", RegexConstStrings::SWS),
          Token("\""),
          TokenRegex("((" + RegexConstStrings::qdtext + ")|(" + RegexConstStrings::quoted_pair + "))*"),
          Token("\"")
         )
       {
      }

      virtual ~TokenQuotedString(void) {
      }

    protected:
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ParserResult result = _sequence.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENQUOTEDSTRING_HPP__
