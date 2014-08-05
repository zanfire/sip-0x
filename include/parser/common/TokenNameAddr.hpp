#if !defined(SIP0X_PARSER_TOKENNAMEADDR_HPP__)
#define SIP0X_PARSER_TOKENNAMEADDR_HPP__


#include "parser/base/TokenContainer.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"
#include "parser/base/Operators.hpp"

#include "parser/common/RegexConstStrings.hpp"
#include "parser/common/TokenPresets.hpp"
#include "parser/common/TokenQuotedString.hpp"

#include "parser/common/TokenAbsoluteURI.hpp"
#include "parser/sip/TokenSIPURI.hpp"

#include "parser/factory/Factory.hpp"

namespace Sip0x
{
  namespace Parser
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
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ReadResult result = _alternative.read(iss, ctx);
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

      virtual FactoryContext* create_factory(FactoryContext* parent) const override {
        return new FactoryContextNameAddr();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENNAMEADDR_HPP__
