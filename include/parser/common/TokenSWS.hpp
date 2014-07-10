#if !defined(SIP0X_PARSER_TOKENSWS_HPP__)
#define SIP0X_PARSER_TOKENSWS_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"
#include "parser/base/Operators.hpp"

#include "parser/common/TokenLWS.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // SWS  =  [LWS] ; sep whitespace
    class TokenSWS : public TokenAbstract {

    protected:
      Occurrence<TokenLWS> _occurrence;

    public:
      TokenSWS(void) : TokenAbstract("SWS"), _occurrence(TokenLWS(), 0, 1)
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSWS");
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult result = _occurrence.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSWS_HPP__
