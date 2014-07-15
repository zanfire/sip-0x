#if !defined(SIP0X_PARSER_TOKENQUOTEDPAIR_HPP__)
#define SIP0X_PARSER_TOKENQUOTEDPAIR_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"
#include "parser/base/Operators.hpp"

#include "parser/common/TokenLWS.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // quoted-pair  =  "\" (%x00-09 / %x0B-0C / %x0E-7F)
    class TokenQuotedPair : public TokenAbstract {

    protected:
      TokenRegex _regex;

    public:
      TokenQuotedPair(void) : TokenAbstract("SWS"), _regex("QuotedPair", "\\\\(()|)")
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSWS");
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult result = _occurrence.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENQUOTEDPAIR_HPP__
