#if !defined(SIP0X_PARSER_TOKENNAMEADDR_HPP__)
#define SIP0X_PARSER_TOKENNAMEADDR_HPP__


#include "parser/tokens/TokenContainer.hpp"
#include "parser/tokens/Token.hpp"
#include "parser/tokens/TokenRegex.hpp"
#include "parser/tokens/Operators.hpp"

#include "parser/tokens/RegexConstStrings.hpp"
#include "parser/tokens/TokenPresets.hpp"
#include "parser/tokens/TokenQuotedString.hpp"

#include "parser/tokens/TokenAbsoluteURI.hpp"
#include "parser/tokens/TokenSIPURI.hpp"

#include "parser/factory/Factory.hpp"

namespace sip0x
{
  namespace parser
  {
    // addr-spec      =  SIP-URI / SIPS-URI / absoluteURI
    class TokenAddrSpec : public TokenAbstract {
    protected:
      Alternative<TokenSIPURI, TokenAbsoluteURI> _alternative;

    public:
      TokenAddrSpec(void) : TokenAbstract("TokenAddrSpec"),
        _alternative(
        TokenSIPURI(),
        TokenAbsoluteURI()
        )
      {
      }


    protected:
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ParserResult result = _alternative.read(iss, ctx);
        return result;
      }
    };

    // name-addr      =  [ display-name ] LAQUOT addr-spec RAQUOT
    // display-name   =  *(token LWS)/ quoted-string
    class TokenNameAddr : public TokenContainer<Sequence<Occurrence<Alternative<TokenRegex, TokenQuotedString>>, TokenLAQUOT, TokenAddrSpec, TokenRAQUOT>> {
    public:
      TokenNameAddr(void) : TokenContainer("TokenNameAddr", 
        Sequence<Occurrence<Alternative<TokenRegex, TokenQuotedString>>, TokenLAQUOT, TokenAddrSpec, TokenRAQUOT>(
        Occurrence<Alternative<TokenRegex, TokenQuotedString>>(
          Alternative<TokenRegex, TokenQuotedString>(
            TokenRegex("(" + RegexConstStrings::token + RegexConstStrings::LWS + ")*"),
            TokenQuotedString()
          ), 0, 1
          ), 
          TokenLAQUOT(), 
          TokenAddrSpec(),
          TokenRAQUOT()
         ), false)
      {
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextNameAddr();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENNAMEADDR_HPP__
