#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_LANGUAGE_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_LANGUAGE_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"



#include "parser/tokens/TokenSIPMethod.hpp"
#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace Parser
  {

    // Content-Language  =  "Content-Language" HCOLON
    //                      language-tag *(COMMA language-tag)
    // language-tag      =  primary-tag *( "-" subtag )
    // primary-tag       =  1*8ALPHA
    // subtag            =  1*8ALPHA
    class TokenSIPMessageHeader_Content_Language : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Content_Language() : TokenSIPMessageHeader_base("Content-Language", "Content\\-Language",
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

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_LANGUAGE_HPP__
