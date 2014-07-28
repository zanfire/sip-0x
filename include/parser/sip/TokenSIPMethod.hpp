#if !defined(SIP0X_PARSER_TOKENSIPMETHOD_HPP__)
#define SIP0X_PARSER_TOKENSIPMETHOD_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/factory/FactoryContextValue.hpp"


namespace Sip0x
{
  namespace Parser
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
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMethod");
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _alternative.read(iss, ctx);
      }


      virtual FactoryContext* create_factory(FactoryContext* parent) const override {
        return new FactoryContextSIPMethod();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPMETHOD_HPP__
