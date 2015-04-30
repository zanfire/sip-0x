#if !defined(SIP0X_PARSER_TOKENUSERINFO_HPP__)
#define SIP0X_PARSER_TOKENUSERINFO_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include "parser/tokens/RegexConstStrings.hpp"

#include "parser/factory/FactoryContextSIPURI.hpp"

// unreserved = alphanum / mark
// mark = "-" / "_" / "." / "!" / "~" / "*" / "'" / "(" / ")"

// ABNF
// userinfo         =  ( user / telephone-subscriber ) [ ":" password ] "@"
// user             =  1*( unreserved / escaped / user-unreserved )
// user-unreserved  =  "&" / "=" / "+" / "$" / "," / ";" / "?" / "/"
// password         =  *( unreserved / escaped / "&" / "=" / "+" / "$" / "," )

namespace sip0x
{
  namespace parser
  {
    // userinfo         =  ( user / telephone-subscriber ) [ ":" password ] "@"
    // user             =  1*( unreserved / escaped / user-unreserved )
    // user-unreserved  =  "&" / "=" / "+" / "$" / "," / ";" / "?" / "/"
    // password         =  *( unreserved / escaped /
    //                     "&" / "=" / "+" / "$" / "," )
    class TokenUserInfo : public TokenAbstract {

    protected:
      Sequence<TokenRegex, Occurrence<Sequence<Token, TokenRegex>>, Token> _sequence;
      
    public:
      TokenUserInfo(void) : TokenAbstract("TokenUserInfo"),
            _sequence(
            TokenRegex("username", "(" + RegexConstStrings::unreserved + "|" + RegexConstStrings::escaped + "|" + RegexConstStrings::sip_user_unreserved + ")+"), 
            Occurrence<Sequence<Token, TokenRegex>>
            (
              Sequence<Token, TokenRegex>
              (
                Token(":"),
                TokenRegex("password", "(" + RegexConstStrings::unreserved + "|" + RegexConstStrings::escaped + "|" + RegexConstStrings::sip_password_unreserved + ")*")
              ), 
            0, 1, true),
            Token("@")
        ) 
      {
      }

    protected:
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _sequence.read(iss, ctx);
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextUserInfo();
      }

    };
  }
}

#endif // SIP0X_PARSER_TOKENIPV6_HPP__
