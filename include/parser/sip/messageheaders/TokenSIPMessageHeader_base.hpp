#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_BASE_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_BASE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"

#include "parser/common/TokenPresets.hpp"

#include "parser/factory/FactoryContextSIPMessageHeader.hpp"

namespace Sip0x
{
  namespace Parser
  {
    template<class Tok>
    class TokenSIPMessageHeader_base : public TokenAbstract {

    protected:
      Sequence<TokenRegex, TokenHCOLON, Tok> _sequence;
      
    public:
      TokenSIPMessageHeader_base(std::string name, std::string fieldregex, Tok& token) : TokenAbstract(name),
        _sequence
        (
          TokenRegex(fieldregex),
          TokenHCOLON(),
          token
        )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMessageHeader");
      }

      virtual ~TokenSIPMessageHeader_base(void) { }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        ReadResult r = _sequence.read(iss, ctx);
        return r;
      }

      virtual FactoryContext* create_factory(FactoryContext* parent) const override {
        return new FactoryContextSIPMessageHeader();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_BASE_HPP__
