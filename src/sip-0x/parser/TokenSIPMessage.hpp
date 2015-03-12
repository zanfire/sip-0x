#if !defined(SIP0X_PARSER_TOKENSIPMESSAGE_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"
#include "parser/base/TokenOctects.hpp"

#include "parser/common/RegexConstStrings.hpp"

#include "parser/sip/TokenSIPRequestLine.hpp"
#include "parser/sip/TokenSIPStatusLine.hpp"
#include "parser/sip/TokenSIPMessageHeader.hpp"

#include "parser/factory/FactoryContextSIPMessage.hpp"

namespace sip0x
{
  namespace Parser
  {
    class TokenSIPMessage : public TokenAbstract {

    protected:
      Sequence<Alternative<TokenSIPRequestLine, TokenSIPStatusLine>, Occurrence<TokenSIPMessageHeader>, TokenCRLF, Occurrence<TokenOctects>> _sequence;
      
    public:
      TokenSIPMessage(void) : TokenAbstract("SIPMessage"),
        _sequence(
        Alternative<TokenSIPRequestLine, TokenSIPStatusLine>(TokenSIPRequestLine(), TokenSIPStatusLine()),
        Occurrence<TokenSIPMessageHeader>(TokenSIPMessageHeader(), 0, -1, true),
        TokenCRLF(),
        Occurrence<TokenOctects>(TokenOctects(), 0, 1, true))
      {
        _sequence.disable_factory(true);
      }

    protected:
      virtual ReadResult handle_read(sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _sequence.read(iss, ctx);
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextSIPMessage();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGE_HPP__
