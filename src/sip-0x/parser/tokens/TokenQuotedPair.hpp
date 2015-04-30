#if !defined(SIP0X_PARSER_TOKENQUOTEDPAIR_HPP__)
#define SIP0X_PARSER_TOKENQUOTEDPAIR_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Token.hpp"
#include "parser/tokens/TokenRegex.hpp"
#include "parser/tokens/Operators.hpp"

#include "parser/tokens/TokenLWS.hpp"

namespace Sip0x
{
  namespace parser
  {
    // quoted-pair  =  "\" (%x00-09 / %x0B-0C / %x0E-7F)
    class TokenQuotedPair : public TokenAbstract {

    protected:
      TokenRegex _regex;

    public:
      TokenQuotedPair(void) : TokenAbstract("SWS"), _regex("QuotedPair", "\\\\(()|)")
      {
        _logger = LoggerFactory::get_logger("Sip0x.Parser.TokenSWS");
      }

    protected:
      virtual ParserResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ParserResult result = _occurrence.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENQUOTEDPAIR_HPP__
