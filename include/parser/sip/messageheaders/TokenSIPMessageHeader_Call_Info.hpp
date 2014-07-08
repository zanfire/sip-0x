#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CALLINFO_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CALLINFO_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/common/TokenLWS.hpp"

#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace Sip0x
{
  namespace Parser
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
          TokenRegex("[0-9]+"),
          TokenLWS(),
          TokenSIPMethod()
        )
      )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMessageHeader_CSeq");
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CALLINFO_HPP__
