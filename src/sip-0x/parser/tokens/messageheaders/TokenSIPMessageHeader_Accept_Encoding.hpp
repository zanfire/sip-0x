#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_ENCODING_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_ENCODING_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"



#include "parser/tokens/TokenSIPMethod.hpp"
#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

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
