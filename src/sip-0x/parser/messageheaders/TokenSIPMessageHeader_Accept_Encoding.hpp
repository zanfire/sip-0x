#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_ENCODING_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_ENCODING_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"



#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace Parser
  {

    // Accept-Encoding  =  "Accept-Encoding" HCOLON
    //                      [ encoding *(COMMA encoding) ]
    // encoding         =  codings *(SEMI accept-param)
    // codings          =  content-coding / "*"
    // content-coding   =  token
    class TokenSIPMessageHeader_Accept_Encoding : public TokenSIPMessageHeader_base<Sequence<TokenDigits, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Accept_Encoding() : TokenSIPMessageHeader_base("Accept-Encoding", "Accept\\-Encoding",
        Sequence<TokenDigits, TokenLWS, TokenSIPMethod>
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

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_ENCODING_HPP__
