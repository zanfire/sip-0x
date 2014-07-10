#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_TYPE_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_TYPE_HPP__

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
    // Content-Type     =  ( "Content-Type" / "c" ) HCOLON media-type
    // media-type       =  m-type SLASH m-subtype *(SEMI m-parameter)
    // m-type           =  discrete-type / composite-type
    // discrete-type    =  "text" / "image" / "audio" / "video"
    //                     / "application" / extension-token
    // composite-type   =  "message" / "multipart" / extension-token
    // extension-token  =  ietf-token / x-token
    // ietf-token       =  token
    // x-token          =  "x-" token
    // m-subtype        =  extension-token / iana-token
    // iana-token       =  token
    // m-parameter      =  m-attribute EQUAL m-value
    // m-attribute      =  token
    // m-value          =  token / quoted-string
    class TokenSIPMessageHeader_Content_Type : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>>{

    protected:

    public:
      //
      TokenSIPMessageHeader_Content_Type() : TokenSIPMessageHeader_base("Content-Type", "(Content\\-Type)|(c)",
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

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_TYPE_HPP__
