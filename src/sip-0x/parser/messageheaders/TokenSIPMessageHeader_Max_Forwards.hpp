#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_MAXFORWARDS_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_MAXFORWARDS_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace Parser
  {

    // Max-Forwards  =  "Max-Forwards" HCOLON 1*DIGIT
    class TokenSIPMessageHeader_Max_Forwards : public TokenSIPMessageHeader_base<TokenDigits> {
    public:
      TokenSIPMessageHeader_Max_Forwards() : TokenSIPMessageHeader_base("Max-Forwards", "Max\\-Forwards", TokenDigits())
      {
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_MAXFORWARDS_HPP__
