#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/common/RegexConstStrings.hpp"

#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace Parser
  {

    // Accept         =  "Accept" HCOLON
    //                    [ accept-range *(COMMA accept-range) ]
    // accept-range   =  media-range *(SEMI accept-param)
    // media-range    =  ( "*/*"
    //                   / ( m-type SLASH "*" )
    //                   / ( m-type SLASH m-subtype )
    //                   ) *( SEMI m-parameter )
    // accept-param   =  ("q" EQUAL qvalue) / generic-param
    // qvalue         =  ( "0" [ "." 0*3DIGIT ] )
    //                   / ( "1" [ "." 0*3("0") ] )
    // generic-param  =  token [ EQUAL gen-value ]
    // gen-value      =  token / host / quoted-string
    class TokenSIPMessageHeader_Accept : public TokenSIPMessageHeader_base<Sequence<TokenDigits, TokenRegex, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Accept() : TokenSIPMessageHeader_base("Accept", "Accept",
        Sequence<TokenDigits, TokenRegex, TokenSIPMethod>
        (
          TokenDigits(),
          TokenRegex("LWS", RegexConstStrings::LWS),
          TokenSIPMethod()
        )
      )
      {
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_HPP__
