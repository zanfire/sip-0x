#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_VIA_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_VIA_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/common/TokenLWS.hpp"

#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace Sip0x
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
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMessageHeader_Via_param_sent_protocol");
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _sequence.read(iss);
        return r;
      }
    };


    // via-parm          =  sent-protocol LWS sent-by *( SEMI via-params )
    class TokenSIPMessageHeader_Via_param : public TokenAbstract {

    protected:
      Sequence<TokenSIPMessageHeader_Via_param_sent_protocol, TokenLWS, TokenHostport, Occurrence<Token, TokenRegex>> _sequence;

    public:
      TokenSIPMessageHeader_Via_param(void) : TokenAbstract("SIPMethod"),
        _sequence(
        TokenSIPMessageHeader_Via_param_sent_protocol(),
        TokenLWS(),
        TokenHostport(),
        Occurrence<Token, TokenRegex>(
          Token(";"),
          TokenRegex(),
          0, -1
        )
        )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMethod");
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _sequence.read(iss);
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
    class TokenSIPMessageHeader_Via_params: public TokenAbstract {

    protected:
      Alternative<
        Sequence<Token, Token, TokenRegex>,
        Sequence<Token, Token, TokenHost>,
        Sequence<Token, Token, TokenHost>,
        Sequence<Token, Token, TokenHost>,
        TokenGenericParam
      >
    public:
      TokenSIPMessageHeader_Via_params(void) : TokenAbstract("SIPMethod"),
        _sequence(
        TokenSIPMessageHeader_Via_param_sent_protocol(),
        TokenLWS(),
        TokenHostport(),
        Occurrence<Token, TokenRegex>(
        Token(";"),
        TokenRegex(),
        0, -1
        )
        )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMethod");
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _sequence.read(iss);
        return r;
      }
    };

    // Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKnashds9
    // Via               =  ( "Via" / "v" ) HCOLON via-parm *(COMMA via-parm)
    // via-parm          =  sent-protocol LWS sent-by *( SEMI via-params )
    // via-params        =  via-ttl / via-maddr
    //                      / via-received / via-branch
    //                      / via-extension
    // via-ttl           =  "ttl" EQUAL ttl
    // via-maddr         =  "maddr" EQUAL host
    // via-received      =  "received" EQUAL (IPv4address / IPv6address)
    // via-branch        =  "branch" EQUAL token
    // via-extension     =  generic-param
    // sent-protocol     =  protocol-name SLASH protocol-version
    //                      SLASH transport
    // protocol-name     =  "SIP" / token
    // protocol-version  =  token
    // transport         =  "UDP" / "TCP" / "TLS" / "SCTP"
    //                      / other-transport
    // sent-by           =  host [ COLON port ]
    // ttl               =  1*3DIGIT ; 0 to 255
    class TokenSIPMessageHeader_Via : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      TokenSIPMessageHeader_Via() : TokenSIPMessageHeader_base("Via", "(Via)|(v)",
        Sequence<TokenRegex, TokenLWS, TokenSIPMethod>
        (
          TokenRegex("[0-9]+"),
          TokenLWS(),
          TokenSIPMethod()
        )
      )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMessageHeader_Via");
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_VIA_HPP__
