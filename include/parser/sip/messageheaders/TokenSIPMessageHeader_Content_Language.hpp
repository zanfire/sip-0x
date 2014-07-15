#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_LANGUAGE_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_LANGUAGE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"



#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace Sip0x
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

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_LANGUAGE_HPP__
