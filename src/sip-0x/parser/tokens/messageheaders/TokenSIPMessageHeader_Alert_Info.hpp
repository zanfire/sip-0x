#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ALERT_INFO_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ALERT_INFO_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"



#include "parser/tokens/TokenSIPMethod.hpp"
#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace parser
  {

    // Alert-Info   =  "Alert-Info" HCOLON alert-param *(COMMA alert-param)
    // alert-param  =  LAQUOT absoluteURI RAQUOT *( SEMI generic-param )
    class TokenSIPMessageHeader_Alert_Info : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Alert_Info() : TokenSIPMessageHeader_base("Alert-Info", "Alert\\-Info",
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

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ALERT_INFO_HPP__
