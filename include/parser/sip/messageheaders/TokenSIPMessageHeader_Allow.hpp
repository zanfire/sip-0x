#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ALLOW_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ALLOW_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"



#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace Sip0x
{
  namespace Parser
  {

    // Allow  =  "Allow" HCOLON [Method *(COMMA Method)]
    class TokenSIPMessageHeader_Allow : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Allow() : TokenSIPMessageHeader_base("Allow", "Allow",
        Sequence<TokenRegex, TokenLWS, TokenSIPMethod>
        (
          TokenRegex("[0-9]+"),
          TokenLWS(),
          TokenSIPMethod()
        )
      )
      {
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ALLOW_HPP__
