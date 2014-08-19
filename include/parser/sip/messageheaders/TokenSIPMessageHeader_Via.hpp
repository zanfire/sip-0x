#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_VIA_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_VIA_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"


#include "parser/common/TokenGenericParam.hpp"

#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace Parser
  {
    // sent-protocol     =  protocol-name SLASH protocol-version
    //                      SLASH transport
    // protocol-name     =  "SIP" / token
    // protocol-version  =  token
    // transport         =  "UDP" / "TCP" / "TLS" / "SCTP"
    //                      / other-transport
    class TokenSIPMessageHeader_Via_param_sent_protocol : public TokenAbstract {

    protected:
      Sequence<TokenRegex, Token, TokenRegex, Token , TokenRegex> _sequence;

    public:
      TokenSIPMessageHeader_Via_param_sent_protocol(void) : TokenAbstract("Via_param_sent_protocol"),
        _sequence(
          TokenRegex(RegexConstStrings::token),
          Token("/"),
          TokenRegex(RegexConstStrings::token),
          Token("/"),
          TokenRegex(RegexConstStrings::token)
        )
      {
      }

    protected:
      virtual ReadResult handle_read(sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ReadResult r = _sequence.read(iss, ctx);
        return r;
      }
    };

    // via-params        =  via-ttl / via-maddr
    //                      / via-received / via-branch
    //                      / via-extension
    // via-ttl           =  "ttl" EQUAL ttl
    // via-maddr         =  "maddr" EQUAL host
    // via-received      =  "received" EQUAL (IPv4address / IPv6address)
    // via-branch        =  "branch" EQUAL token
    // via-extension     =  generic-param
    // ttl               =  1*3DIGIT ; 0 to 255
    class TokenSIPMessageHeader_Via_params : public TokenAbstract {

    protected:
      Alternative <
        Sequence<Token, Token, TokenRegex>,
        Sequence<Token, Token, TokenHost>,
        Sequence<Token, Token, TokenRegex>,
        Sequence<Token, Token, Alternative<TokenIPv4, TokenIPv6>>,
        TokenGenericParam> _alternative;
    public:
      TokenSIPMessageHeader_Via_params(void) : TokenAbstract("TokenSIPMessageHeader_Via_params"),
        _alternative(
        Sequence<Token, Token, TokenRegex>(Token("ttl"), Token("="), TokenRegex("[0-5]{1,3}")),
        Sequence<Token, Token, TokenHost>(Token("maddr"), Token("="), TokenHost()),
        Sequence<Token, Token, TokenRegex>(Token("branch"), Token("="), TokenRegex(RegexConstStrings::token)),
        Sequence<Token, Token, Alternative<TokenIPv4, TokenIPv6>>(Token("received"), Token("="), Alternative<TokenIPv4, TokenIPv6>(TokenIPv4(), TokenIPv6())),
        TokenGenericParam()
        )
      {
      }

    protected:
      virtual ReadResult handle_read(sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ReadResult r = _alternative.read(iss, ctx);
        return r;
      }
    };

    // via-parm          =  sent-protocol LWS sent-by *( SEMI via-params )
    class TokenSIPMessageHeader_Via_param : public TokenAbstract {

    protected:
      Sequence<TokenSIPMessageHeader_Via_param_sent_protocol, TokenLWS, TokenHostport, Occurrence<Sequence<TokenSEMI, TokenSIPMessageHeader_Via_params>>> _sequence;

    public:
      TokenSIPMessageHeader_Via_param(void) : TokenAbstract("TokenSIPMessageHeader_Via_param_sent_protocol"),
        _sequence(
        TokenSIPMessageHeader_Via_param_sent_protocol(),
        TokenLWS(),
        TokenHostport(),
        Occurrence<Sequence<TokenSEMI, TokenSIPMessageHeader_Via_params>>(
          Sequence<TokenSEMI, TokenSIPMessageHeader_Via_params>(
            TokenSEMI(),
            TokenSIPMessageHeader_Via_params()
          ),
          0, -1
        )
        )
      {
      }

    protected:
      virtual ReadResult handle_read(sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ReadResult r = _sequence.read(iss, ctx);
        return r;
      }
    };

    // Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKnashds9
    // Via               =  ( "Via" / "v" ) HCOLON via-parm *(COMMA via-parm)
    class TokenSIPMessageHeader_Via : public TokenSIPMessageHeader_base<Sequence<TokenSIPMessageHeader_Via_param, Occurrence<Sequence<TokenCOMMA, TokenSIPMessageHeader_Via_param>>>> {

    public:
      TokenSIPMessageHeader_Via() : TokenSIPMessageHeader_base("Via", "(Via)|(v)",
        Sequence<TokenSIPMessageHeader_Via_param, Occurrence<Sequence<TokenCOMMA, TokenSIPMessageHeader_Via_param>>>
        (
          TokenSIPMessageHeader_Via_param(),
          Occurrence<Sequence<TokenCOMMA, TokenSIPMessageHeader_Via_param>>
          (
          Sequence<TokenCOMMA, TokenSIPMessageHeader_Via_param>
            (
              TokenCOMMA(),
              TokenSIPMessageHeader_Via_param()
            ), 0, -1
          )
        )
      )
      {
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_VIA_HPP__
