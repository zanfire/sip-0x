#if !defined(SIP0X_PARSER_TOKENHOSTPORT_HPP__)
#define SIP0X_PARSER_TOKENHOSTPORT_HPP__

#include "parser/tokens/TokenContainer.hpp"
#include "parser/tokens/TokenIPv4.hpp"
#include "parser/tokens/TokenIPv6.hpp"
#include "parser/tokens/TokenRegex.hpp"
#include "parser/tokens/Operators.hpp"

#include "parser/factory/FactoryContextSIPURI.hpp"

namespace sip0x
{
  namespace parser
  {
    // hostname         =  *( domainlabel "." ) toplabel [ "." ]
    // domainlabel      =  alphanum / alphanum *( alphanum / "-" ) alphanum
    // toplabel         =  ALPHA / ALPHA *( alphanum / "-" ) alphanum
    class TokenHostname : public TokenContainer<Sequence<Occurrence<Sequence<TokenRegex, Token>>, TokenRegex, Occurrence<Token>>> {

    public:
      TokenHostname(void) : TokenContainer("hostname", Sequence<Occurrence<Sequence<TokenRegex, Token>>, TokenRegex, Occurrence<Token>>(
        Occurrence<Sequence<TokenRegex, Token>>
        (
          Sequence<TokenRegex, Token>
          (
            TokenRegex("domain", "(([A-Za-z-0-9]+)|([A-Za-z-0-9]+\\-[A-Za-z-0-9]+))+"),
            Token(".")
          ), 0, -1, true
        ),
        TokenRegex("top", "(([A-Za-z])|([A-Za-z]([A-Za-z-0-9]+\\-)+[A-Za-z-0-9]+))+"),
        Occurrence<Token>(Token("."), 0, 1, true)
        ), true)
      {
      }
    };


    class TokenHost : public TokenContainer<Alternative<TokenIPv4, TokenIPv6, TokenHostname>> {

    public:
      TokenHost(void) : TokenContainer("TokenHost", Alternative<TokenIPv4, TokenIPv6, TokenHostname>(TokenIPv4(), TokenIPv6(), TokenHostname()), true) {
      }
    };
   

    // host             =  hostname / IPv4address / IPv6reference  
    // hostport         =  host [ ":" port ]
    class TokenHostport: public TokenAbstract {

    protected:
      Sequence<TokenHost, Occurrence<Sequence<Token, TokenDigits>>> _sequence;
    public:
      TokenHostport(void) : TokenAbstract("hostport"), _sequence(TokenHost(), 
        Occurrence<Sequence<Token, TokenDigits>>
        (
        Sequence<Token, TokenDigits>
          (
            Token(":"),
            TokenDigits()
          ), 0, 1, true
        )
      ) {
      }

      virtual ~TokenHostport(void) {
      }

    protected:
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _sequence.read(iss, ctx);
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextHostPort();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENHOSTPORT_HPP__
