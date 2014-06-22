#if !defined(SIP0X_PARSER_TOKENSIPURI_HPP__)
#define SIP0X_PARSER_TOKENSIPURI_HPP__

#include "parser/base/Operators.hpp"

#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"
#include "parser/sip/TokenURIParameter.hpp"

// ABNF: SIP_URI = lit("sip:") > -userinfo > hostport >> uri_parameters >> -headers;
// SIP-URI          =  "sip:" [ userinfo ] hostport uri-parameters [ headers ]

namespace Sip0x
{
  namespace Parser
  {
    class TokenSIPURI : public OpAbstract {

    protected:
      Sequence<Token, TokenUserInfo, Token, Occurrence<Token>, Occurrence<Sequence<Token, TokenURIParameter>>> _sequence;

    public:
      TokenSIPURI(void) : OpAbstract() {
        //add_token("sip:");
        //std::shared_ptr<TokenAbstract> userinfo(new TokenUserInfo());
        //add_occurrence("userinfo", userinfo, 0, 1);
        // hostport
        // add uri_params
        // header
      }

      virtual ~TokenSIPURI(void) {
        //for each (ParserAbstract* var in _rules) {
        //    delete var;
        //}
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPURI_HPP__
