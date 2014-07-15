#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_DISPOSITION_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_DISPOSITION_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"



#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace Sip0x
{
  namespace Parser
  {

    // Content-Disposition   =  "Content-Disposition" HCOLON
    //                          disp-type *( SEMI disp-param )
    // disp-type             =  "render" / "session" / "icon" / "alert"
    //                          / disp-extension-token
    // 
    // disp-param            =  handling-param / generic-param
    // handling-param        =  "handling" EQUAL
    //                          ( "optional" / "required"
    //                          / other-handling )
    // other-handling        =  token
    // disp-extension-token  =  token
    class TokenSIPMessageHeader_Content_Disposition : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Content_Disposition() : TokenSIPMessageHeader_base("CSeq", "CSeq",
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

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_DISPOSITION_HPP__
