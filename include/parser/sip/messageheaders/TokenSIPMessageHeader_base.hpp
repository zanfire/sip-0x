#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_BASE_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_BASE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"

#include "parser/common/TokenHCOLON.hpp"


namespace Sip0x
{
  namespace Parser
  {
    template<class Seq>
    class TokenSIPMessageHeader_base : public TokenAbstract {

    protected:
      Sequence<TokenRegex, TokenHCOLON, Seq> _sequence;
      
    public:
      TokenSIPMessageHeader_base(std::string name, std::string fieldregex, Seq& sequence) : TokenAbstract(name),
        _sequence
        (
          TokenRegex(fieldregex),
          TokenHCOLON(),
          sequence
        )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMessageHeader");
      }

      virtual ~TokenSIPMessageHeader_base(void) { }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _sequence.read(iss);
        return r;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_BASE_HPP__
