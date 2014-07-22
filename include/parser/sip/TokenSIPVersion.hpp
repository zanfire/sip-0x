#if !defined(SIP0X_PARSER_TOKENSIPVERSION_HPP__)
#define SIP0X_PARSER_TOKENSIPVERSION_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/factory/FactoryContextSIPVersion.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // SIP-Version    =  "SIP" "/" 1*DIGIT "." 1*DIGIT
    class TokenSIPVersion : public TokenAbstract {

    protected:
      Sequence<Token, TokenDigits, Token, TokenDigits> _sequence;
      
    public:
      TokenSIPVersion(void) : TokenAbstract("SIPResponse"), 
        _sequence(Token("SIP/"), TokenDigits(), Token("."), TokenDigits())
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPVersion");
      }

      virtual ~TokenSIPVersion(void) { }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _sequence.read(iss, ctx);
      }

      virtual FactoryContext* create_factory(FactoryContext* parent) const override {
        return new FactoryContextSIPVersion();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPVERSION_HPP__
