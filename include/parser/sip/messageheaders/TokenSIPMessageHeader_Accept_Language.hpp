#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_LANGUAGE_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_LANGUAGE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"



#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace Sip0x
{
  namespace Parser
  {

    // Accept-Language  =  "Accept-Language" HCOLON
    //                      [ language *(COMMA language) ]
    // language         =  language-range *(SEMI accept-param)
    // language-range   =  ( ( 1*8ALPHA *( "-" 1*8ALPHA ) ) / "*" )
    class TokenSIPMessageHeader_Accept_Language : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>>{

    protected:

    public:
      //
      TokenSIPMessageHeader_Accept_Language() : TokenSIPMessageHeader_base("Accept-Language", "Accept\\-Language",
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

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_LANGUAGE_HPP__
