#if !defined(SIP0X_PARSER_TOKENUIRPARAMETER_HPP__)
#define SIP0X_PARSER_TOKENUIRPARAMETER_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/OpSequence.hpp"
#include "parser/base/OpOccurrence.hpp"
#include "parser/base/OpAlternative.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/common/RegexConstStrings.hpp"

// unreserved = alphanum / mark
// mark = "-" / "_" / "." / "!" / "~" / "*" / "'" / "(" / ")"

// ABNF
// uri-parameters    =  *( ";" uri-parameter)
// uri-parameter     =  transport-param / user-param / method-param / ttl-param / maddr-param / lr-param / other-param
//
// transport-param   =  "transport=" ( "udp" / "tcp" / "sctp" / "tls" / other-transport)
// other-transport   =  token
// user-param        =  "user=" ( "phone" / "ip" / other-user)
// other-user        =  token
// method-param      =  "method=" Method
// ttl-param         =  "ttl=" ttl
// maddr-param       =  "maddr=" host
// lr-param          =  "lr"
// other-param       =  pname [ "=" pvalue ]
// pname             =  1*paramchar
// pvalue            =  1*paramchar
// paramchar         =  param-unreserved / unreserved / escaped
// param-unreserved  =  "[" / "]" / "/" / ":" / "&" / "+" / "$"

namespace Sip0x
{
  namespace Parser
  {
    class TokenURIParameter : public OpAlternative {

    public:
      TokenURIParameter(void) : OpAlternative() {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenURIParameter");
        _name = "TokenURIParameter";

        // "transport=" ( "udp" / "tcp" / "sctp" / "tls" / other-transport)
        std::shared_ptr<OpSequence> seq(new OpSequence());
        seq->add_token("transport=");
        std::shared_ptr<OpAlternative> alt(new OpAlternative());
        alt->add_token("udp");
        alt->add_token("tcp");
        alt->add_token("sctp");
        alt->add_token("tls");
        alt->add_regex("other-transport", RegexConstStrings::token);
        seq->add("transport", alt);

        add(seq);
      }

      virtual ~TokenURIParameter(void) {
      }

    protected:
      //void add(std::string field, )

    };
  }
}

#endif // SIP0X_PARSER_TOKENUIRPARAMETERS_HPP__
