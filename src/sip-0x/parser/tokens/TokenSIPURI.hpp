#if !defined(SIP0X_PARSER_TOKENSIPURI_HPP__)
#define SIP0X_PARSER_TOKENSIPURI_HPP__

#include "parser/tokens/Operators.hpp"

#include "parser/tokens/Token.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include "parser/tokens/TokenHostPort.hpp"

#include "parser/tokens/TokenUserInfo.hpp"
#include "parser/tokens/TokenURIParameter.hpp"
#include "parser/tokens/TokenURIHeaders.hpp"

#include "parser/factory/FactoryContextSIPURI.hpp"


namespace sip0x
{
  namespace parser
  {
    // ABNF: SIP_URI = lit("sip:") > -userinfo > hostport >> uri_parameters >> -headers;
    // SIP-URI          =  "sip:" [ userinfo ] hostport uri-parameters [ headers ]
    class TokenSIPURI : public TokenAbstract {

    protected:
      Sequence<TokenRegex, Occurrence<TokenUserInfo>, TokenHostport, TokenURIParameters, TokenURIHeaders> _sequence;

    public:
      TokenSIPURI(void) : TokenAbstract("SIPURI"), _sequence(
        TokenRegex("sip[s]?:"),
        Occurrence<TokenUserInfo>(TokenUserInfo(), 0, 1),
        TokenHostport(),
        TokenURIParameters(),
        TokenURIHeaders())
      {
      }

      virtual ~TokenSIPURI(void) {
      }

      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _sequence.read(iss, ctx);
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextSIPURI();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPURI_HPP__
