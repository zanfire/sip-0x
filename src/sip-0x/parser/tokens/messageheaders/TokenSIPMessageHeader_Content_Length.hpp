#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_LENGTH_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_LENGTH_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace Parser
  {

    // Content-Length  =  ( "Content-Length" / "l" ) HCOLON 1*DIGIT
    class TokenSIPMessageHeader_Content_Length : public TokenSIPMessageHeader_base<TokenDigits>{
    public:
      TokenSIPMessageHeader_Content_Length() : TokenSIPMessageHeader_base("Content-Length", "(Content\\-Length)|(l)", TokenDigits()) {}
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_LENGTH_HPP__
