#if !defined(SIP0X_PARSER_TOKENUIRPARAMETER_HPP__)
#define SIP0X_PARSER_TOKENUIRPARAMETER_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"

#include "parser/tokens/Token.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include "parser/tokens/RegexConstStrings.hpp"

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

namespace sip0x
{
  namespace parser
  {
    template<class Alt>
    class TokenURIParam_base : public TokenAbstract {
    protected:
      Sequence<Token, Token, Alt> _sequence;

    public:
      TokenURIParam_base(std::string name, std::string param, const Alt& alternative) : 
        TokenAbstract(name), _sequence(Token(param), Token("="), alternative) {}

    protected:
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _sequence.read(iss, ctx);
      }


      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextURIParameter();
      }
    };

    class TokenURIParam_transport : public TokenURIParam_base<Alternative<Token, Token, Token, TokenRegex>> {
    public:
      TokenURIParam_transport(void) : TokenURIParam_base
        (
          "URIParam_transport",
          "transport", 
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
        "user",
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
        "method",
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
          "ttl",
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
          "maddr",
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
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ParserResult r = _sequence.read(iss, ctx);
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
        ) 
      {
      }

    protected:
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _alternative.read(iss, ctx);
      }
    };

    // *(";" uri-parameter)
    class TokenURIParameters : public TokenAbstract {
    protected:
      Occurrence<Sequence<Token, TokenURIParameter>> _occurrene;

    public:
      TokenURIParameters(void) : TokenAbstract("URIParameter"), _occurrene(
        Sequence<Token, TokenURIParameter>(Token(";"), TokenURIParameter()), 0, -1, true) 
      {
      }

    protected:
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _occurrene.read(iss, ctx);
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextURIParameters();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENUIRPARAMETERS_HPP__
