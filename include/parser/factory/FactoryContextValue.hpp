#if !defined(SIP0X_PARSER_FACTORYCONTEXTEX_HPP__)
#define SIP0X_PARSER_FACTORYCONTEXTEX_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/factory/FactoryContext.hpp"

#include "protocol/SIP.hpp"

namespace Sip0x
{
  namespace Parser
  {
    using namespace Sip0x::Protocol;

    template<typename T>
    class FactoryContextValue : public FactoryContext {
    protected:
      T _value;
    public:

      T get(void) { return _value; }
    
    };

   
    class FactoryContextSIPMethod : public FactoryContextValue<SIPMethod> {
    protected:
    public:
      virtual void create(std::string const& text) override {
        _value = convSIPMethodFromChars(text.c_str());
      }
    };

    class FactoryContextDigits : public FactoryContextValue<long> {
    protected:
    public:
      virtual void create(std::string const& text) override {
        _value = atol(text.c_str());
      }
    };

  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXTEX_HPP__
