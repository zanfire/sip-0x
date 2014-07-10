#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_TO_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_TO_HPP__

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

    // To        =  ( "To" / "t" ) HCOLON ( name-addr
    //              / addr-spec ) *( SEMI to-param )
    // to-param  =  tag-param / generic-param
    class TokenSIPMessageHeader_To : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_To() : TokenSIPMessageHeader_base("To", "To",
        Sequence<TokenRegex, TokenLWS, TokenSIPMethod>
        (
          TokenRegex("[0-9]+"),
          TokenLWS(),
          TokenSIPMethod()
        )
      )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMessageHeader_To");
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CSEQ_HPP__
