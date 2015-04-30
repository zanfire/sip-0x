#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTACT_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_CONTACT_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include "parser/tokens/TokenGenericParam.hpp"
#include "parser/tokens/TokenNameAddr.hpp"

#include "parser/tokens/TokenSIPMethod.hpp"
#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace parser
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
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ParserResult r = _alternative.read(iss, ctx);
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
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ParserResult r = _sequence.read(iss, ctx);
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
