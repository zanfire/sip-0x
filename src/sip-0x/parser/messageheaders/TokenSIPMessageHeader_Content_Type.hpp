#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_TYPE_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_TYPE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/common/TokenMType.hpp"
#include "parser/common/TokenQuotedString.hpp"

#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace Parser
  {
    // Content-Type     =  ( "Content-Type" / "c" ) HCOLON media-type
    // media-type       =  m-type SLASH m-subtype *(SEMI m-parameter)
    // m-subtype        =  extension-token / iana-token
    // iana-token       =  token
    // m-parameter      =  m-attribute EQUAL m-value
    // m-attribute      =  token
    // m-value          =  token / quoted-string
    class TokenSIPMessageHeader_Content_Type : public TokenSIPMessageHeader_base < Sequence<TokenMType, TokenSLASH, TokenRegex, Occurrence<Sequence<TokenSEMI, Sequence<TokenRegex, TokenEQUAL, Alternative<TokenRegex, TokenQuotedString>>>> > > {

    public:
      //
      TokenSIPMessageHeader_Content_Type() : TokenSIPMessageHeader_base("Content-Type", "(Content\\-Type)|(c)",
        Sequence<TokenMType, TokenSLASH, TokenRegex, Occurrence<Sequence<TokenSEMI, Sequence<TokenRegex, TokenEQUAL, Alternative<TokenRegex, TokenQuotedString>>>>>
        (
          TokenMType(),
          TokenSLASH(),
          TokenRegex("(" + RegexConstStrings::token + ")|(x\\-" + RegexConstStrings::token + ")"),
          Occurrence<Sequence<TokenSEMI, Sequence<TokenRegex, TokenEQUAL, Alternative<TokenRegex, TokenQuotedString>>>>
          (
            Sequence<TokenSEMI, Sequence<TokenRegex, TokenEQUAL, Alternative<TokenRegex, TokenQuotedString>>>
            (
              TokenSEMI(),
              Sequence<TokenRegex, TokenEQUAL, Alternative<TokenRegex, TokenQuotedString>>
              (
                  TokenRegex(RegexConstStrings::token),
                  TokenEQUAL(),
                  Alternative<TokenRegex, TokenQuotedString>(TokenRegex(RegexConstStrings::token), TokenQuotedString())
              )
            ), 0, -1
          )
        )
        )
      {
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_TYPE_HPP__
