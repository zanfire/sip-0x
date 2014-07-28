#if !defined(SIP0X_PARSER_TOKENCONTAINER_HPP__)
#define SIP0X_PARSER_TOKENCONTAINER_HPP__

#include "parser/base/TokenAbstract.hpp"

namespace Sip0x
{
  namespace Parser
  {
    template<class T>
    class TokenContainer : public TokenAbstract {
    protected:
      T _token;
      bool _disable_factory;

    public:
      TokenContainer(std::string name, T token, bool disable_factory) : TokenAbstract(name), _token(token), _disable_factory(disable_factory) {
      }

      virtual FactoryContext* create_factory(FactoryContext* parent) const override {
        if (_disable_factory) {
          return nullptr;
        }
        else {
          return new FactoryContext();
        }
      }

    protected:
   
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _token.read(iss, ctx);
      }
    };
  }
}

#endif // SIP0X_PARSER_OCCURRENCE_HPP__