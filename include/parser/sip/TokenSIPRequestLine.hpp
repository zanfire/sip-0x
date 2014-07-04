#if !defined(SIP0X_PARSER_TOKENSIPREQUESTLINE_HPP__)
#define SIP0X_PARSER_TOKENSIPREQUESTLINE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"


#include "parser/sip/TokenSIPURI.hpp"
#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/TokenSIPVersion.hpp"

namespace Sip0x
{
  namespace Parser
  {

    // Request-Line   =  Method SP Request-URI SP SIP-Version CRLF
    // Request-URI    =  SIP-URI / SIPS-URI / absoluteURI
    class TokenSIPRequestLine : public TokenAbstract {

    protected:
      // TODO: SIPURI should be replaced by RequestURI.
      Sequence<TokenSIPMethod, Token, TokenSIPURI , Token, TokenSIPVersion, Token> _sequence;
      
    public:
      TokenSIPRequestLine(void) : TokenAbstract("SIPRequestLine"), 
        _sequence
        (
          TokenSIPMethod(),
          Token(" "),
          TokenSIPURI(),
          Token(" "),
          TokenSIPVersion(),
          Token("\r\n")
        )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPRequestLine");
      }

      virtual ~TokenSIPRequestLine(void) { }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _sequence.read(iss);
        return r;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPREQUESTLINE_HPP__
