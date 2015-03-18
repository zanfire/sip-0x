#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_FROM_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_FROM_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include "parser/tokens/TokenNameAddr.hpp"
#include "parser/tokens/TokenGenericParam.hpp"

#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace Parser
  {
    // From        =  ( "From" / "f" ) HCOLON from-spec
    // from-spec   =  ( name-addr / addr-spec ) *( SEMI from-param )
    // from-param  =  tag-param / generic-param
    // tag-param   =  "tag" EQUAL token
    class TokenSIPMessageHeader_From : public TokenSIPMessageHeader_base < Sequence<Alternative<TokenNameAddr, TokenAddrSpec>, Occurrence<Sequence<TokenSEMI, TokenGenericParam>>> > {
    public:
      TokenSIPMessageHeader_From() : TokenSIPMessageHeader_base("From", "(From)|(f)",
        Sequence<Alternative<TokenNameAddr, TokenAddrSpec>, Occurrence<Sequence<TokenSEMI, TokenGenericParam>>> (
            Alternative<TokenNameAddr, TokenAddrSpec>(
              TokenNameAddr(),
              TokenAddrSpec()
            ),
            Occurrence<Sequence<TokenSEMI, TokenGenericParam>>
            (
              Sequence<TokenSEMI, TokenGenericParam>(TokenSEMI(), TokenGenericParam()), 0, -1)
            )
        )
      {
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_FROM_HPP__
