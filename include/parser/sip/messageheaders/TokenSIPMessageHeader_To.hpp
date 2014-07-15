#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_TO_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_TOHPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/common/TokenNameAddr.hpp"
#include "parser/common/TokenGenericParam.hpp"

#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // To        =  ( "To" / "t" ) HCOLON ( name-addr
    //          / addr-spec ) *( SEMI to-param )
    // to-param  =  tag-param / generic-param
    class TokenSIPMessageHeader_To : public TokenSIPMessageHeader_base < Sequence<Alternative<TokenNameAddr, TokenAddrSpec>, Occurrence<Sequence<TokenSEMI, TokenGenericParam>>> > {
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
