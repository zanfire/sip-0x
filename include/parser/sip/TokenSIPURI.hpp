#if !defined(SIP0X_PARSER_TOKENSIPURI_HPP__)
#define SIP0X_PARSER_TOKENSIPURI_HPP__

#include "parser/base/Operators.hpp"

#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/common/TokenHostPort.hpp"

#include "parser/sip/TokenUserInfo.hpp"
#include "parser/sip/TokenURIParameter.hpp"
#include "parser/sip/TokenURIHeaders.hpp"

#include "parser/factory/FactoryContextSIPURI.hpp"


namespace Sip0x
{
  namespace Parser
  {
    // ABNF: SIP_URI = lit("sip:") > -userinfo > hostport >> uri_parameters >> -headers;
    // SIP-URI          =  "sip:" [ userinfo ] hostport uri-parameters [ headers ]
    class TokenSIPURI : public TokenAbstract {

    protected:
      Sequence<TokenRegex, TokenUserInfo, TokenHostport, TokenURIParameters, TokenURIHeaders> _sequence;

    public:
      TokenSIPURI(void) : TokenAbstract("SIPURI"), _sequence(
        TokenRegex("sip[s]?:"),
        TokenUserInfo(),
        TokenHostport(),
        TokenURIParameters(),
        TokenURIHeaders())
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPURI");
      }

      virtual ~TokenSIPURI(void) {
      }

      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _sequence.read(iss, ctx);
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextSIPURI();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPURI_HPP__
