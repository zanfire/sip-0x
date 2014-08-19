#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CSEQ_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CSEQ_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"



#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace Parser
  {

    // CSeq  =  "CSeq" HCOLON 1*DIGIT LWS Method
    class TokenSIPMessageHeader_CSeq : public TokenSIPMessageHeader_base<Sequence<TokenDigits, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_CSeq() : TokenSIPMessageHeader_base("CSeq", "CSeq",
        Sequence<TokenDigits, TokenLWS, TokenSIPMethod>
        (
          TokenDigits(),
          TokenLWS(),
          TokenSIPMethod()
        )
      )
      {
        _logger = LoggerManager::get_logger("sip0x.Parser.TokenSIPMessageHeader_CSeq");
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CSEQ_HPP__
