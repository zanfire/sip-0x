#if !defined(SIP0X_PARSER_TOKENSIPMESSAGE_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/common/RegexConstStrings.hpp"

#include "parser/sip/TokenSIPRequest.hpp"
#include "parser/sip/TokenSIPResponse.hpp"

namespace Sip0x
{
  namespace Parser
  {
    class TokenSIPMessage : public TokenAbstract {

    protected:
      Alternative<TokenSIPRequest, TokenSIPResponse> _alternative;
      
    public:
      TokenSIPMessage(void) : TokenAbstract("SIPMessage"), _alternative(TokenSIPRequest(), TokenSIPResponse())
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMessage");
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _alternative.read(iss);
        return r;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGE_HPP__
