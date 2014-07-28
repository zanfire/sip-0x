#if !defined(SIP0X_PARSER_TOKENSIPREQUESTLINE_HPP__)
#define SIP0X_PARSER_TOKENSIPREQUESTLINE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"

#include "parser/common/TokenPresets.hpp"

#include "parser/sip/TokenSIPURI.hpp"
#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/TokenSIPVersion.hpp"

//#include "parser/factory/FactoryContextSIPRequestLine.hpp"

namespace Sip0x
{
  namespace Parser
  {

    // Request-URI    =  SIP-URI / SIPS-URI / absoluteURI
    // Request-Line   =  Method SP Request-URI SP SIP-Version CRLF
    class TokenSIPRequestLine : public TokenAbstract {

    protected:
      // TODO: SIPURI should be replaced by RequestURI.
      Sequence<TokenSIPMethod, TokenSP, TokenSIPURI , TokenSP, TokenSIPVersion, TokenCRLF> _sequence;
      
    public:
      TokenSIPRequestLine() : TokenAbstract("SIPRequestLine"), 
        _sequence
        (
          TokenSIPMethod(),
          TokenSP(),
          TokenSIPURI(),
          TokenSP(),
          TokenSIPVersion(),
          TokenCRLF()
        )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPRequestLine");
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _sequence.read(iss, ctx);
      }

    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPREQUESTLINE_HPP__
