#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_EXTENSION_HEADER_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_EXTENSION_HEADER_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include "parser/tokens/TokenSIPMethod.hpp"
#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace parser
  {
    // extension-header  =  header-name HCOLON header-value
    // header-name       =  token
    // header-value      =  *(TEXT-UTF8char / UTF8-CONT / LWS)
    class TokenSIPMessageHeader_extension_header : public TokenSIPMessageHeader_base<TokenRegex> {

    protected:

    public:
      //
      TokenSIPMessageHeader_extension_header() : TokenSIPMessageHeader_base("header-name", RegexConstStrings::token, TokenRegex("header-value", "((" + RegexConstStrings::TEXT_UTF8char + ")|(" + RegexConstStrings::UTF8_CONT + ")|(" + RegexConstStrings::LWS + "))*"))
      {
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_EXTENSION_HEADER_HPP__
