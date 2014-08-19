#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CALL_ID_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CALL_ID_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"



#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace Parser
  {

    // Call-ID  =  ( "Call-ID" / "i" ) HCOLON callid
    // callid   =  word [ "@" word ]
    class TokenSIPMessageHeader_Call_ID : public TokenSIPMessageHeader_base<Sequence<TokenWord, Occurrence<Sequence<Token, TokenWord>>>> {
    public:
      TokenSIPMessageHeader_Call_ID() : TokenSIPMessageHeader_base("Call-ID", "(Call\\-ID|i)",
        Sequence<TokenWord, Occurrence<Sequence<Token, TokenWord>>>
        (
          TokenWord(),
          Occurrence<Sequence<Token, TokenWord>>(Sequence<Token, TokenWord>(Token("@"), TokenWord()), 0, 1)
        ))
      {
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CALL_ID_HPP__
