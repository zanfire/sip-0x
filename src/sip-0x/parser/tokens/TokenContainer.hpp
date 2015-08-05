#if !defined(SIP0X_PARSER_TOKENCONTAINER_HPP__)
#define SIP0X_PARSER_TOKENCONTAINER_HPP__

#include "parser/tokens/TokenAbstract.hpp"

namespace sip0x
{
  namespace parser
  {
    template<class T>
    class TokenContainer : public TokenAbstract {
    protected:
      const T _token;
      bool _disable_factory = true;

    public:
      TokenContainer(std::string name, const T& token, bool disable_factory) : TokenAbstract(name), _token(token), _disable_factory(disable_factory) {
      }

      virtual FactoryContext* create_factory(void) const override {
        if (_disable_factory) {
          return nullptr;
        }
        else {
          return new FactoryContext();
        }
      }

    protected:
   
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _token.read(iss, ctx);
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENCONTAINER_HPP__
