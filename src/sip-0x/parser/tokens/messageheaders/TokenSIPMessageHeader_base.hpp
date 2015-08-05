#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_BASE_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_BASE_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/TokenRegex.hpp"
#include "parser/tokens/TokenPresets.hpp"
#include "parser/tokens/Operators.hpp"

#include "parser/factory/FactoryContextSIPMessageHeader.hpp"

namespace sip0x
{
  namespace parser
  {
    template<class Tok>
    class TokenSIPMessageHeader_base : public TokenAbstract {

    protected:
      Sequence<TokenRegex, TokenHCOLON, Tok> _sequence;
      
    public:
      TokenSIPMessageHeader_base(std::string name, std::string fieldregex, const Tok& token) : TokenAbstract(name),
        _sequence
        (
          TokenRegex(fieldregex),
          TokenHCOLON(),
          token
        )
      {
      }

      virtual ~TokenSIPMessageHeader_base(void) { }

    protected:
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ParserResult r = _sequence.read(iss, ctx);
        return r;
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextSIPMessageHeader();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_BASE_HPP__
