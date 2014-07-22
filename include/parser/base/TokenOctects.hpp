#if !defined(SIP0X_PARSER_TOKENOCTECTS_HPP__)
#define SIP0X_PARSER_TOKENOCTECTS_HPP__

#include "parser/base/TokenAbstract.hpp"

namespace Sip0x
{
  namespace Parser
  {
    /// This parser expects a specific token and return an instance. 
    class TokenOctects : public TokenAbstract {

    protected:
    uint8_t* _content;
    int _size;

    public:
      TokenOctects() : TokenAbstract("OCTECTS"), _content(nullptr), _size(0) {
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        int rem = iss.remains();
        std::string str = iss.get(rem);
        // TODO: Copy to local buffer...
        return ReadResult(true);
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENOCTECTS_HPP__
