#if !defined(SIP0X_PARSER_TOKENLWS_HPP__)
#define SIP0X_PARSER_TOKENLWS_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"


namespace Sip0x
{
  namespace Parser
  {
    // WSP  =  SP / HTAB ; white space
    // LWS  =  [*WSP CRLF] 1*WSP ; linear whitespace
    class TokenLWS : public TokenAbstract {

    protected:
      TokenRegex _regex;

    public:
      // TODO: LWS = -(*WSP >> CRLF) >> +WSP; // linear whitespace
      TokenLWS(void) : TokenAbstract("LWS"), _regex("LWS", "([ \\x09]*(\r\n){0,1}[ \\x09]+)") {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenLWS");
      }

      virtual ~TokenLWS(void) {
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult result = _regex.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENLWS_HPP__
