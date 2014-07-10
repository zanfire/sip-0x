#if !defined(SIP0X_PARSER_TOKENQUOTEDSTRING_HPP__)
#define SIP0X_PARSER_TOKENQUOTEDSTRING_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"
#include "parser/base/Operators.hpp"

#include "parser/common/TokenSWS.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // quoted-string  =  SWS DQUOTE *(qdtext / quoted-pair ) DQUOTE
    // qdtext         =  LWS / %x21 / %x23-5B / %x5D-7E / UTF8-NONASCII
    // quoted-pair  =  "\" (%x00-09 / %x0B-0C / %x0E-7F)
    class TokenQuotedString : public TokenAbstract {

    protected:
      Sequence<TokenSWS, Token, TokenRegex, Token> _sequence;

    public:
      TokenQuotedString(void) : TokenAbstract("TokenQuotedString"), 
        _sequence(
          TokenSWS(),
          Token("\""),
          TokenRegex(""),
          Token("\"")
         )
       {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenQuotedString");
      }

      virtual ~TokenQuotedString(void) {
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult result = _sequence.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENQUOTEDSTRING_HPP__
