#if !defined(SIP0X_PARSER_TOKENSIPREQUESTLINE_HPP__)
#define SIP0X_PARSER_TOKENSIPREQUESTLINE_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"

#include "parser/tokens/TokenPresets.hpp"

#include "parser/tokens/TokenSIPURI.hpp"
#include "parser/tokens/TokenSIPMethod.hpp"
#include "parser/tokens/TokenSIPVersion.hpp"

//#include "parser/factory/FactoryContextSIPRequestLine.hpp"

namespace sip0x
{
  namespace parser
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
      }

    protected:
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _sequence.read(iss, ctx);
      }

    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPREQUESTLINE_HPP__
