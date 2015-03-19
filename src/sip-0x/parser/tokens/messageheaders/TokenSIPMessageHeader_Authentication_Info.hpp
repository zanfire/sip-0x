#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_AUTHENTICATION_INFO_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_AUTHENTICATION_INFO_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"



#include "parser/tokens/TokenSIPMethod.hpp"
#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace parser
  {

    // Authentication-Info  =  "Authentication-Info" HCOLON ainfo
    //                         *(COMMA ainfo)
    // ainfo                =  nextnonce / message-qop
    //                          / response-auth / cnonce
    //                          / nonce-count
    // nextnonce            =  "nextnonce" EQUAL nonce-value
    // response-auth        =  "rspauth" EQUAL response-digest
    // response-digest      =  LDQUOT *LHEX RDQUOT
    class TokenSIPMessageHeader_Authentication_Info : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Authentication_Info() : TokenSIPMessageHeader_base("Authentication-Info", "Authentication\\-Info",
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

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_AUTHENTICATION_INFO_HPP__
