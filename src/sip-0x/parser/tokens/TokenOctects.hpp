#if !defined(SIP0X_PARSER_TOKENOCTECTS_HPP__)
#define SIP0X_PARSER_TOKENOCTECTS_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/factory/FactoryContext.hpp"

namespace sip0x
{
  namespace parser
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
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* /*ctx*/) const override {
        int rem = iss.remains();
        std::string str = iss.get(rem);
        // TODO: Copy to local buffer...
        return ParserResult(true, 0, 0);
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContext();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENOCTECTS_HPP__
