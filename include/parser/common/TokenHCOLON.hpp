#if !defined(SIP0X_PARSER_TOKENHCOLON_HPP__)
#define SIP0X_PARSER_TOKENHCOLON_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"


namespace Sip0x
{
  namespace Parser
  {
    // WSP  =  SP / HTAB ; white space
    // LWS  =  [*WSP CRLF] 1*WSP ; linear whitespace
    // SWS  =  [LWS] ; sep whitespace
    // HCOLON = *(SP / HTAB) ":" SWS
    class TokenHCOLON : public TokenAbstract {

    protected:
      TokenRegex _regex;

    public:
      // TODO: Define better (doesn't handle CRLF)
      TokenHCOLON(void) : TokenAbstract("HCOLON"), _regex("LWS", "([\\x09 ])*:([\\x09 ])*") {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenLWS");
      }

      virtual ~TokenHCOLON(void) {
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult result = _regex.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENHCOLON_HPP__
