#if !defined(SIP0X_PARSER_TOKENUIRPARAMETER_HPP__)
#define SIP0X_PARSER_TOKENUIRPARAMETER_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"

#include "parser/base/Token.hpp"
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
    template<class Alt>
    class TokenURIParam_base : public TokenAbstract {
    protected:
      Sequence<Token, Alt> _sequence;

    public:
      TokenURIParam_base(std::string name, std::string param, Alt& alternative) : TokenAbstract(name), _sequence(Token(param), alternative) {}

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _sequence.read(iss, ctx);
        return r;
      }
    };

    class TokenURIParam_transport : public TokenURIParam_base<Alternative<Token, Token, Token, TokenRegex>> {
    public:
      TokenURIParam_transport(void) : TokenURIParam_base
        (
          "URIParam_transport",
          "transport=", 
          Alternative<Token, Token, Token, TokenRegex>
          (
            Token("udp"),
            Token("tcp"),
            Token("sctp"),
            TokenRegex("other-transport", RegexConstStrings::token)
          )
        ) 
      {
      }
    };

    // user-param        =  "user=" ( "phone" / "ip" / other-user)
    class TokenURIParam_user : public TokenURIParam_base<Alternative<Token, Token, TokenRegex>> {
    public:
      TokenURIParam_user(void) : TokenURIParam_base
        (
        "URIParam_user",
        "user=",
        Alternative<Token, Token, TokenRegex>
        (
        Token("phone"),
        Token("ip"),
        TokenRegex("other-user", RegexConstStrings::token)
        )
        )
      {
      }
    };
    
    // method-param      =  "method=" Method
    // TODO: Complete.
    class TokenURIParam_method : public TokenURIParam_base<Alternative<Token, TokenRegex>> {
    public:
      TokenURIParam_method(void) : TokenURIParam_base(
        "URIParam_method",
        "method=",
        Alternative<Token, TokenRegex>
        (
          Token("INVITE"),
          TokenRegex("other-method", RegexConstStrings::token)
        )
        )
      {
      }
    };

    // ttl-param         =  "ttl=" ttl
    // Complete
    class TokenURIParam_ttl : public TokenURIParam_base<TokenRegex> {
    public:
      TokenURIParam_ttl(void) : TokenURIParam_base
        (
          "URIParam_ttl",
          "ttl=",
          TokenRegex("other-method", RegexConstStrings::token)
        )
      {
      }
    };

    // maddr-param       =  "maddr=" host
    // TODO: Complete
    class TokenURIParam_maddr : public TokenURIParam_base<TokenRegex> {
    public:
      TokenURIParam_maddr(void) : TokenURIParam_base
        (
          "URIParam_maddr",
          "maddr=",
          TokenRegex("other-method", RegexConstStrings::token)
        )
      {
      }
    };

    // lr-param          =  "lr"
    // directlly the token ";lr"


    class TokenURIParam_other : public TokenAbstract {
    protected:
      Sequence<TokenRegex, Token, TokenRegex> _sequence;
    public:
      TokenURIParam_other(void) : TokenAbstract("URIParam_other"), _sequence
        (
        TokenRegex("pname", "p"),
        Token("="),
        TokenRegex("pvalue", RegexConstStrings::token)
        )
      {
      }
    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _sequence.read(iss, ctx);
        return r;
      }
    };


    // uri-parameter     =  transport-param / user-param / method-param / ttl-param / maddr-param / lr-param / other-param
    class TokenURIParameter : public TokenAbstract {
    protected:
      Alternative<TokenURIParam_transport, TokenURIParam_user, TokenURIParam_maddr, TokenURIParam_method, TokenURIParam_ttl, Token, TokenURIParam_other> _alternative;

    public:
      TokenURIParameter(void) : TokenAbstract("URIParameter"), _alternative(
          TokenURIParam_transport(), 
          TokenURIParam_user(), 
          TokenURIParam_maddr(), 
          TokenURIParam_method(),
          TokenURIParam_ttl(), 
          Token("lr"), 
          TokenURIParam_other()
        ) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenURIParameter");
        _name = "TokenURIParameter";

      }

      virtual ~TokenURIParameter(void) {
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _alternative.read(iss, ctx);
        return r;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENUIRPARAMETERS_HPP__
