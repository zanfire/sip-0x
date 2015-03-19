#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ALLOW_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ALLOW_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"



#include "parser/tokens/TokenSIPMethod.hpp"
#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace parser
  {

    // Allow  =  "Allow" HCOLON [Method *(COMMA Method)]
    class TokenSIPMessageHeader_Allow : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Allow() : TokenSIPMessageHeader_base("Allow", "Allow",
        Sequence<TokenRegex, TokenLWS, TokenSIPMethod>
        (
          TokenDigits(),
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
