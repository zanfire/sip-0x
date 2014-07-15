#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_ENCODING_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_ENCODING_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"



#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace Sip0x
{
  namespace Parser
  {

    // Accept-Encoding  =  "Accept-Encoding" HCOLON
    //                      [ encoding *(COMMA encoding) ]
    // encoding         =  codings *(SEMI accept-param)
    // codings          =  content-coding / "*"
    // content-coding   =  token
    class TokenSIPMessageHeader_Accept_Encoding : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Accept_Encoding() : TokenSIPMessageHeader_base("Accept-Encoding", "Accept\\-Encoding",
        Sequence<TokenRegex, TokenLWS, TokenSIPMethod>
        (
          TokenRegex("[0-9]+"),
          TokenLWS(),
          TokenSIPMethod()
        )
      )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMessageHeader_Accept_Encoding");
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_ACCEPT_ENCODING_HPP__
