#if !defined(SIP0X_PARSER_TOKENUIHYEADERS_HPP__)
#define SIP0X_PARSER_TOKENUIHYEADERS_HPP__

#include "parser/tokens/TokenContainer.hpp"
#include "parser/tokens/Operators.hpp"

#include "parser/tokens/Token.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include "parser/tokens/RegexConstStrings.hpp"

namespace sip0x
{
  namespace parser
  {
    // header          =  hname "=" hvalue
    // hname           =  1*( hnv-unreserved / unreserved / escaped )
    // hvalue          =  *( hnv-unreserved / unreserved / escaped )
    // hnv-unreserved  =  "[" / "]" / "/" / "?" / ":" / "+" / "$"
    class TokenURIHeader : public TokenContainer<Sequence<TokenRegex, Token, TokenRegex>> {
    
    public:
      TokenURIHeader(void) : TokenContainer("TokenURIHeader", 
        Sequence<TokenRegex, Token, TokenRegex>(
          TokenRegex("((" + RegexConstStrings::hnv_unreserved + ")|(" + RegexConstStrings::unreserved + ")|(" + RegexConstStrings::escaped + ")|)+"),
          Token("="), 
          TokenRegex("((" + RegexConstStrings::hnv_unreserved + ")|(" + RegexConstStrings::unreserved + ")|(" + RegexConstStrings::escaped + ")|)*")
        ), true) {}
      
    protected:
      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextURIParameter();
      }
    };

    // headers         =  "?" header *( "&" header )
    class TokenURIHeaders : public TokenContainer<Occurrence<Sequence<Token, TokenURIHeader, Occurrence<Sequence<Token, TokenURIHeader>>>>> {
    
    public:
      TokenURIHeaders(void) : TokenContainer("TokenURIHeaders",
        Occurrence<Sequence<Token, TokenURIHeader, Occurrence<Sequence<Token, TokenURIHeader>>>>
        (
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
            , 0, -1, true)
          )
        , 0, -1, true), true)
      {
      }

    protected:
      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextURIParameters();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENUIRPARAMETERS_HPP__
