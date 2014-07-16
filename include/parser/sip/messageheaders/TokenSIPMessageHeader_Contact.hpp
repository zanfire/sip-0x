#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTACT_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTACT_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/common/TokenGenericParam.hpp"
#include "parser/common/TokenNameAddr.hpp"

#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // contact-params     =  c-p-q / c-p-expires
    //                       / contact-extension
    // c-p-q              =  "q" EQUAL qvalue
    // c-p-expires        =  "expires" EQUAL delta-seconds
    // contact-extension  =  generic-param
    // delta-seconds      =  1*DIGIT
    class TokenSIPMessageHeader_Contact_params : public TokenAbstract {

    protected:
      Alternative <
        Sequence<Token, TokenEQUAL, TokenRegex>,
        Sequence<Token, TokenEQUAL, TokenDigits>,
        TokenGenericParam> _alternative;
    public:
      TokenSIPMessageHeader_Contact_params(void) : TokenAbstract("TokenSIPMessageHeader_Contact_params"),
        _alternative(
        Sequence<Token, TokenEQUAL, TokenRegex>(Token("q"), TokenEQUAL(), TokenRegex(RegexConstStrings::qvalue)),
        Sequence<Token, TokenEQUAL, TokenDigits>(Token("expires"), TokenEQUAL(), TokenDigits()),
        TokenGenericParam()
        )
      {
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _alternative.read(iss);
        return r;
      }
    };


    // contact-param  =  (name-addr / addr-spec) *(SEMI contact-params)
    class TokenSIPMessageHeader_Contact_param : public TokenAbstract {

    protected:
      Sequence<Alternative<TokenNameAddr, TokenAddrSpec>, Occurrence<Sequence<TokenSEMI, TokenSIPMessageHeader_Contact_params>>> _sequence;

    public:
      TokenSIPMessageHeader_Contact_param(void) : TokenAbstract("TokenSIPMessageHeader_Contact_param"),
        _sequence(
          Alternative<TokenNameAddr, TokenAddrSpec>(TokenNameAddr(), TokenAddrSpec()), 
          Occurrence<Sequence<TokenSEMI, TokenSIPMessageHeader_Contact_params>>(
            Sequence<TokenSEMI, TokenSIPMessageHeader_Contact_params>(TokenSEMI(), TokenSIPMessageHeader_Contact_params()), 0, -1
          )
        )
      {
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _sequence.read(iss);
        return r;
      }
    };

    // Contact        =  ("Contact" / "m" ) HCOLON
    //                   ( STAR / (contact-param *(COMMA contact-param)))
    class TokenSIPMessageHeader_Contact : public TokenSIPMessageHeader_base<Alternative<TokenSTAR, Sequence<TokenSIPMessageHeader_Contact_param, Occurrence<Sequence<TokenCOMMA, TokenSIPMessageHeader_Contact_param>>>>> {
    public:
      //
      TokenSIPMessageHeader_Contact() : TokenSIPMessageHeader_base("Contact", "(Contact)|(m)",
        Alternative<TokenSTAR, Sequence<TokenSIPMessageHeader_Contact_param, Occurrence<Sequence<TokenCOMMA, TokenSIPMessageHeader_Contact_param>>>>
        (
          TokenSTAR(),
          Sequence<TokenSIPMessageHeader_Contact_param, Occurrence<Sequence<TokenCOMMA, TokenSIPMessageHeader_Contact_param>>>(
            TokenSIPMessageHeader_Contact_param(),
            Occurrence<Sequence<TokenCOMMA, TokenSIPMessageHeader_Contact_param>>(
            Sequence<TokenCOMMA, TokenSIPMessageHeader_Contact_param>(
              TokenCOMMA(),
              TokenSIPMessageHeader_Contact_param()
            ), 0, -1)
          )
        )
      )
      {
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTACT_HPP__
