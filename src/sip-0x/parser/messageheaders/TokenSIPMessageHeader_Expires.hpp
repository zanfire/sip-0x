#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_EXPIRES_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_EXPIRES_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"



#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace Parser
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
