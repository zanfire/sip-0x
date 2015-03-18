#if !defined(SIP0X_PARSER_TOKENSIPMESSAGE_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGE_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"
#include "parser/tokens/TokenOctects.hpp"

#include "parser/tokens/RegexConstStrings.hpp"

#include "parser/tokens/TokenSIPRequestLine.hpp"
#include "parser/tokens/TokenSIPStatusLine.hpp"
#include "parser/tokens/TokenSIPMessageHeader.hpp"

#include "parser/factory/FactoryContextSIPMessage.hpp"

namespace sip0x
{
  namespace parser
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
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _sequence.read(iss, ctx);
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextSIPMessage();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGE_HPP__
