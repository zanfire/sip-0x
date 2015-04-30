#if !defined(SIP0X_PARSER_TOKENSIPVERSION_HPP__)
#define SIP0X_PARSER_TOKENSIPVERSION_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/Token.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include "parser/factory/FactoryContextSIPVersion.hpp"

namespace sip0x
{
  namespace parser
  {
    // SIP-Version    =  "SIP" "/" 1*DIGIT "." 1*DIGIT
    class TokenSIPVersion : public TokenAbstract {

    protected:
      Sequence<Token, TokenDigits, Token, TokenDigits> _sequence;
      
    public:
      TokenSIPVersion(void) : TokenAbstract("SIPResponse"), 
        _sequence(Token("SIP/"), TokenDigits(), Token("."), TokenDigits())
      {
      }

      virtual ~TokenSIPVersion(void) { }

    protected:
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _sequence.read(iss, ctx);
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextSIPVersion();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPVERSION_HPP__
