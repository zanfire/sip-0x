#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CALL_ID_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CALL_ID_HPP__

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

    // Call-ID  =  ( "Call-ID" / "i" ) HCOLON callid
    // callid   =  word [ "@" word ]
    class TokenSIPMessageHeader_Call_ID : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      TokenSIPMessageHeader_Call_ID() : TokenSIPMessageHeader_base("Call-ID", "(Call\\-ID|i)",
        Sequence<TokenRegex, TokenLWS, TokenSIPMethod>
        (
          TokenRegex("[0-9]+"),
          TokenLWS(),
          TokenSIPMethod()
        )
      )
      {
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CALL_ID_HPP__
