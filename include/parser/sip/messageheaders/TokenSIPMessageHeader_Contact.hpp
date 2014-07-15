#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTACT_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTACT_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"



#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace Sip0x
{
  namespace Parser
  {

    // Contact        =  ("Contact" / "m" ) HCOLON
    //                   ( STAR / (contact-param *(COMMA contact-param)))
    // contact-param  =  (name-addr / addr-spec) *(SEMI contact-params)
    // name-addr      =  [ display-name ] LAQUOT addr-spec RAQUOT
    // addr-spec      =  SIP-URI / SIPS-URI / absoluteURI
    // display-name   =  *(token LWS)/ quoted-string
    // 
    // contact-params     =  c-p-q / c-p-expires
    //                       / contact-extension
    // c-p-q              =  "q" EQUAL qvalue
    // c-p-expires        =  "expires" EQUAL delta-seconds
    // contact-extension  =  generic-param
    // delta-seconds      =  1*DIGIT
    class TokenSIPMessageHeader_Contact : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Contact() : TokenSIPMessageHeader_base("Contact", "Conctact",
        Sequence<TokenRegex, TokenLWS, TokenSIPMethod>
        (
          TokenRegex("[0-9]+"),
          TokenLWS(),
          TokenSIPMethod()
        )
      )
      {
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTACT_HPP__
