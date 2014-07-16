#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_EXTENSION_HEADER_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_EXTENSION_HEADER_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace Sip0x
{
  namespace Parser
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
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMessageHeader_extension_header");
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_EXTENSION_HEADER_HPP__
