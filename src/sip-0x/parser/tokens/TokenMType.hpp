#if !defined(SIP0X_PARSER_TOKENMTYPE_HPP__)
#define SIP0X_PARSER_TOKENMTYPE_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Token.hpp"
#include "parser/tokens/TokenRegex.hpp"
#include "parser/tokens/Operators.hpp"

#include "parser/tokens/RegexConstStrings.hpp"
#include "parser/tokens/TokenPresets.hpp"
#include "parser/tokens/TokenQuotedString.hpp"

namespace sip0x
{
  namespace parser
  {
    // m-type           =  discrete-type / composite-type
    // discrete-type    =  "text" / "image" / "audio" / "video"
    //                     / "application" / extension-token
    // composite-type   =  "message" / "multipart" / extension-token
    // extension-token  =  ietf-token / x-token
    // ietf-token       =  token
    // x-token          =  "x-" token
    class TokenMType : public TokenAbstract {

    protected:
      Alternative<Alternative<Token, Token, Token, Token, Token, TokenRegex>, Alternative<Token, Token, TokenRegex>> _alternative;

    public:
      TokenMType(void) : TokenAbstract("TokenMType"),
        _alternative(
          Alternative<Token, Token, Token, Token, Token, TokenRegex>(Token("text"), Token("image"), Token("audio"), Token("video"), Token("application"),
          TokenRegex("(" + RegexConstStrings::token + ")|(x\\-" + RegexConstStrings::token + ")")),
          Alternative<Token, Token, TokenRegex>(Token("message"), Token("multipart"), TokenRegex("(" + RegexConstStrings::token + ")|(x\\-" + RegexConstStrings::token + ")"))
        )
      {
      }


    protected:
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ParserResult result = _alternative.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENMTYPE_HPP__
