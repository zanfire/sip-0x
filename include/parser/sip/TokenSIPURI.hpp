#if !defined(SIP0X_PARSER_TOKENSIPURI_HPP__)
#define SIP0X_PARSER_TOKENSIPURI_HPP__

#include "parser/base/Operators.hpp"

#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"
#include "parser/sip/TokenUserInfo.hpp"
#include "parser/common/TokenHostPort.hpp"
#include "parser/sip/TokenURIParameter.hpp"

// ABNF: SIP_URI = lit("sip:") > -userinfo > hostport >> uri_parameters >> -headers;
// SIP-URI          =  "sip:" [ userinfo ] hostport uri-parameters [ headers ]

namespace Sip0x
{
  namespace Parser
  {
    class TokenSIPURI : public TokenAbstract {

    protected:
      Sequence<TokenRegex, TokenUserInfo, TokenHostport, Occurrence<Sequence<Token, TokenURIParameter>>> _sequence;

    public:
      TokenSIPURI(void) : TokenAbstract("SIPURI"), _sequence(
        TokenRegex("sip[s]?:"),
        TokenUserInfo(),
        TokenHostport(),
        Occurrence<Sequence<Token, TokenURIParameter>>
        (
          Sequence<Token, TokenURIParameter>
          (
            Token(";"), 
            TokenURIParameter()
          ), 0, -1)
        ) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPURI");
      }

      virtual ~TokenSIPURI(void) {
      }

      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ReadResult result = _sequence.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPURI_HPP__
