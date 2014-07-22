#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ALERT_INFO_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ALERT_INFO_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"



#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace Sip0x
{
  namespace Parser
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
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMessageHeader_Alert_Info");
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ALERT_INFO_HPP__
