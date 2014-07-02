#if !defined(SIP0X_PARSER_TOKENHOSTPORT_HPP__)
#define SIP0X_PARSER_TOKENHOSTPORT_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/common/TokenIPv4.hpp"
#include "parser/common/TokenIPv6.hpp"
#include "parser/base/TokenRegex.hpp"
#include "parser/base/Operators.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // hostname         =  *( domainlabel "." ) toplabel [ "." ]
    // domainlabel      =  alphanum / alphanum *( alphanum / "-" ) alphanum
    // toplabel         =  ALPHA / ALPHA *( alphanum / "-" ) alphanum
    class TokenHostname : public TokenAbstract {

    protected:
      Sequence<Occurrence<Sequence<TokenRegex, Token>>, TokenRegex, Occurrence<Token>> _sequence;
    public:
      TokenHostname(void) : TokenAbstract("hostname"), _sequence(
        Occurrence<Sequence<TokenRegex, Token>>
        (
          Sequence<TokenRegex, Token>
          (
            TokenRegex("domain", "(([A-Za-z-0-9]+)|([A-Za-z-0-9]+\\-[A-Za-z-0-9]+))+"),
            Token(".")
          ), 0, -1
        ),
        TokenRegex("top", "(([A-Za-z])|([A-Za-z]([A-Za-z-0-9]+\\-)+[A-Za-z-0-9]+))+"),
        Occurrence<Token>(Token("."), 0, 1)
      ) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenHostname");
      }

      virtual ~TokenHostname(void) {
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult result = _sequence.read(iss, ctx);
        return result;
      }
    };


    class TokenHost : public TokenAbstract {

    protected:
      Alternative<TokenHostname, TokenIPv6, TokenIPv4> _alternative;
    public:
      TokenHost(void) : TokenAbstract("host"), _alternative(TokenHostname(), TokenIPv6(), TokenIPv4()) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenHost");
      }

      virtual ~TokenHost(void) {
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult result = _alternative.read(iss, ctx);
        return result;
      }
    };
   

    // host             =  hostname / IPv4address / IPv6reference  
    // hostport         =  host [ ":" port ]
    class TokenHostport: public TokenAbstract {

    protected:
      Sequence<TokenHost, Occurrence<Sequence<Token, TokenRegex>>> _sequence;
    public:
      TokenHostport(void) : TokenAbstract("hostport"), _sequence(TokenHost(), 
        Occurrence<Sequence<Token, TokenRegex>>
        (
          Sequence<Token, TokenRegex>
          (
            Token(":"),
            TokenRegex("[0-9]+")
          ), 0, 1
        )
      ) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenHostport");
      }

      virtual ~TokenHostport(void) {
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult result = _sequence.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENHOSTPORT_HPP__
