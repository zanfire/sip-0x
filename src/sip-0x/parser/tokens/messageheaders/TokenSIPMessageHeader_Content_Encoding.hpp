#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_ENCODING_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_ENCODING_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"



#include "parser/tokens/TokenSIPMethod.hpp"
#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace parser
  {

    // TODO: add e
    // Content-Encoding  =  ( "Content-Encoding" / "e" ) HCOLON
    //                 content-coding *(COMMA content-coding)
    class TokenSIPMessageHeader_Content_Encoding : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Content_Encoding() : TokenSIPMessageHeader_base("Content-Encoding", "Content\\-Encoding",
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

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_ENCODING_HPP__
