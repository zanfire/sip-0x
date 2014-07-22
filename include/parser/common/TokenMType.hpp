#if !defined(SIP0X_PARSER_TOKENMTYPE_HPP__)
#define SIP0X_PARSER_TOKENMTYPE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"
#include "parser/base/Operators.hpp"

#include "parser/common/RegexConstStrings.hpp"
#include "parser/common/TokenPresets.hpp"
#include "parser/common/TokenQuotedString.hpp"

namespace Sip0x
{
  namespace Parser
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
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ReadResult result = _alternative.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENMTYPE_HPP__
