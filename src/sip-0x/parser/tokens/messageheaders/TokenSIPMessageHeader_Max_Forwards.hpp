#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_MAXFORWARDS_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_MAXFORWARDS_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace parser
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
