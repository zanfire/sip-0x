#if !defined(SIP0X_PARSER_TOKENSIPREQUEST_HPP__)
#define SIP0X_PARSER_TOKENSIPREQUEST_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"

#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/sip/TokenSIPRequestLine.hpp"
#include "parser/sip/TokenSIPMessageHeader.hpp"

namespace Sip0x
{
  namespace Parser
  {

    // Request        =  Request-Line
    //                   *( message-header )
    //                   CRLF
    //                   [ message-body ]
    class TokenSIPRequest : public TokenAbstract {

    protected:
      Sequence<TokenSIPRequestLine, Occurrence<TokenSIPMessageHeader>, TokenCRLF, TokenRegex> _sequence;
      
    public:
      TokenSIPRequest(void) : TokenAbstract("SIPRequest"),
        _sequence(
          TokenSIPRequestLine(), 
          Occurrence<TokenSIPMessageHeader>(TokenSIPMessageHeader(), 0, -1), 
          TokenCRLF(), 
          TokenRegex(".*")
         )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPRequest");
      }

      virtual ~TokenSIPRequest(void) { }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _sequence.read(iss);
        return r;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPREQUEST_HPP__
