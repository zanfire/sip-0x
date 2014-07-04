#if !defined(SIP0X_PARSER_TOKENSIPVERSION_HPP__)
#define SIP0X_PARSER_TOKENSIPVERSION_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"


namespace Sip0x
{
  namespace Parser
  {
    // SIP-Version    =  "SIP" "/" 1*DIGIT "." 1*DIGIT
    class TokenSIPVersion : public TokenAbstract {

    protected:
      Sequence<Token, TokenRegex, Token, TokenRegex> _sequence;
      
    public:
      TokenSIPVersion(void) : TokenAbstract("SIPResponse"), 
        _sequence(Token("SIP/"), TokenRegex("[0-9]+"), Token("."), TokenRegex("[0-9]+"))
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPVersion");
      }

      virtual ~TokenSIPVersion(void) { }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _sequence.read(iss);
        return r;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPVERSION_HPP__
