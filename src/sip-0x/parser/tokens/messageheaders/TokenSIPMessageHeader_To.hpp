#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_TO_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_TO_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include "parser/tokens/TokenNameAddr.hpp"
#include "parser/tokens/TokenGenericParam.hpp"

#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace parser
  {
    // To        =  ( "To" / "t" ) HCOLON ( name-addr
    //          / addr-spec ) *( SEMI to-param )
    // to-param  =  tag-param / generic-param
    class TokenSIPMessageHeader_To : public TokenSIPMessageHeader_base<Sequence<Alternative<TokenNameAddr, TokenAddrSpec>, Occurrence<Sequence<TokenSEMI, TokenGenericParam>>> > {
    public:
      TokenSIPMessageHeader_To() : TokenSIPMessageHeader_base("To", "(To)|(t)",
        Sequence<Alternative<TokenNameAddr, TokenAddrSpec>, Occurrence<Sequence<TokenSEMI, TokenGenericParam>>>(
        Alternative<TokenNameAddr, TokenAddrSpec>(
        TokenNameAddr(),
        TokenAddrSpec()
        ),
        Occurrence<Sequence<TokenSEMI, TokenGenericParam>>(Sequence<TokenSEMI, TokenGenericParam>(TokenSEMI(), TokenGenericParam()), 0, -1)
        )
        )
      {
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_TO_HPP__
