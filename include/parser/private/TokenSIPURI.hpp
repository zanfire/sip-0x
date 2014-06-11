#if !defined(SIP0X_PARSER_TOKENSIPURI_HPP__)
#define SIP0X_PARSER_TOKENSIPURI_HPP__

#include "parser/private/TokenAbstract.hpp"
#include "parser/private/Token.hpp"
#include "parser/private/TokenRegex.hpp"

// ABNF: SIP_URI = lit("sip:") > -userinfo > hostport >> uri_parameters >> -headers;

namespace Sip0x
{
  namespace Parser
  {
    class TokenSIPURI : public TokenAbstract {

    protected:

    public:
      TokenSIPURI(void) : TokenAbstract() {
        //_rules.push_back(new Token("sip:"));
        //_rules.push_back(new TokenRegex("sip:"));
      }

      virtual ~TokenSIPURI(void) {
        //for each (ParserAbstract* var in _rules) {
        //    delete var;
        //}
      }

    protected:
      virtual std::tuple<bool, void*> read(std::istringstream& iss) {
        return std::tuple<bool, void*>(true, nullptr);
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPURI_HPP__
