#if !defined(SIP0X_PARSER_TOKENUIHYEADERS_HPP__)
#define SIP0X_PARSER_TOKENUIHYEADERS_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"

#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/common/RegexConstStrings.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // header          =  hname "=" hvalue
    // hname           =  1*( hnv-unreserved / unreserved / escaped )
    // hvalue          =  *( hnv-unreserved / unreserved / escaped )
    // hnv-unreserved  =  "[" / "]" / "/" / "?" / ":" / "+" / "$"
    class TokenURIHeader : public TokenAbstract {
    protected:
      Sequence<TokenRegex, Token, TokenRegex> _sequence;

    public:
      TokenURIHeader(void) : TokenAbstract("TokenURIHeader"), 
        _sequence(
          TokenRegex("((" + RegexConstStrings::hnv_unreserved + ")|(" + RegexConstStrings::unreserved + ")|(" + RegexConstStrings::escaped + ")|)+"),
          Token("="), 
          TokenRegex("((" + RegexConstStrings::hnv_unreserved + ")|(" + RegexConstStrings::unreserved + ")|(" + RegexConstStrings::escaped + ")|)*")
        ) {}

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _sequence.read(iss, ctx);
      }
    };

    // headers         =  "?" header *( "&" header )
    class TokenURIHeaders : public TokenAbstract {
    protected:
      Occurrence<Sequence<Token, TokenURIHeader, Occurrence<Sequence<Token, TokenURIHeader>>>> _occurrene;

    public:
      TokenURIHeaders(void) : TokenAbstract("TokenURIHeaders"), 
        _occurrene(
        Sequence<Token, TokenURIHeader, Occurrence<Sequence<Token, TokenURIHeader>>>
        (
          Token("?"),
          TokenURIHeader(),
          Occurrence<Sequence<Token, TokenURIHeader>>
          (
            Sequence<Token, TokenURIHeader>
            (
              Token("&"),
              TokenURIHeader()
            )
          , 0, -1)
        ), 0, -1) 
      {
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _occurrene.read(iss, ctx);
      }

      virtual FactoryContext* create_factory(FactoryContext* factory) const override {
        return nullptr;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENUIRPARAMETERS_HPP__
