#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_EXPIRES_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_EXPIRES_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"



#include "parser/tokens/TokenSIPMethod.hpp"
#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace parser
  {

    // CSeq  =  "Expires" HCOLON 1*DIGIT
    class TokenSIPMessageHeader_Expires : public TokenSIPMessageHeader_base<TokenDigits> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Expires() : TokenSIPMessageHeader_base("Expires", "Expires", TokenDigits())
      {
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_EXPIRES_HPP__
