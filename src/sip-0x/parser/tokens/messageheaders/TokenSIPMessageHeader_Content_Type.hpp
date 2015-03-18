#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_TYPE_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTENT_TYPE_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include "parser/tokens/TokenMType.hpp"
#include "parser/tokens/TokenQuotedString.hpp"

#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

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
