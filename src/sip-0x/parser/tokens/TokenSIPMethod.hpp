#if !defined(SIP0X_PARSER_TOKENSIPMETHOD_HPP__)
#define SIP0X_PARSER_TOKENSIPMETHOD_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/Token.hpp"
#include "parser/tokens/TokenRegex.hpp"

#include "parser/factory/FactoryContextValue.hpp"


namespace sip0x
{
  namespace parser
  {
    // Method            =  INVITEm / ACKm / OPTIONSm / BYEm / CANCELm / REGISTERm / extension-method
    class TokenSIPMethod : public TokenAbstract {

    protected:
      Alternative<Token, Token, Token, Token, Token, Token,  TokenRegex> _alternative;
      
    public:
      TokenSIPMethod(void) : TokenAbstract("SIPMethod"), 
        _alternative(
          Token("INVITE"),
          Token("ACK"),
          Token("OPTION"),
          Token("BYE"),
          Token("CANCEL"),
          Token("REGISTER"),
          TokenRegex(RegexConstStrings::token)
        )
      {
      }

    protected:
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _alternative.read(iss, ctx);
      }


      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextSIPMethod();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPMETHOD_HPP__
