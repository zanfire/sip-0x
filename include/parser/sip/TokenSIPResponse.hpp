#if !defined(SIP0X_PARSER_TOKENSIPRESPONSE_HPP__)
#define SIP0X_PARSER_TOKENSIPRESPONSE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"


namespace Sip0x
{
  namespace Parser
  {
    class TokenSIPResponse : public TokenAbstract {

    protected:
      // it is magic ... no is nested template.
      //Sequence<TokenRegex, Occurrence<Sequence<Token, TokenRegex>>, Token> _sequence;
      
    public:
      TokenSIPResponse(void) : TokenAbstract("SIPResponse")
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPResponse");
      }

      virtual ~TokenSIPResponse(void) { }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r; // = _sequence.read(iss, ui);
        return r;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPRESPONSE_HPP__
