#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CALLINFO_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CALLINFO_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"



#include "parser/tokens/TokenSIPMethod.hpp"
#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace parser
  {
    // Call-Info   =  "Call-Info" HCOLON info *(COMMA info)
    // info        =  LAQUOT absoluteURI RAQUOT *( SEMI info-param)
    // info-param  =  ( "purpose" EQUAL ( "icon" / "info"
    //                / "card" / token ) ) / generic-param
    class TokenSIPMessageHeader_Call_Info : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Call_Info() : TokenSIPMessageHeader_base("Call-Info", "Call\\-Info",
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

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CALLINFO_HPP__
