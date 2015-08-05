#if !defined(SIP0X_PARSER_FACTORYCONTEXTEX_HPP__)
#define SIP0X_PARSER_FACTORYCONTEXTEX_HPP__

#include "parser/factory/FactoryContext.hpp"

#include "protocol/SIP.hpp"

namespace sip0x
{
  namespace parser
  {
    //! Templace class for a any generic value.
    //! \remarks This class need to be derived and provide an impl for impl_create.
    template<typename T>
    class FactoryContextValue : public FactoryContext {
    protected:
      T _value;
    public:
      T get(void) { return _value; }
    };

   
    class FactoryContextSIPMethod : public FactoryContextValue<protocol::SIPMethod> {
    protected:
    public:
      virtual void impl_create(void) override {
        _value = protocol::convSIPMethodFromChars(_text.c_str());
      }
    };

    class FactoryContextDigits : public FactoryContextValue<long> {
    protected:
    public:
      virtual void impl_create(void) override {
        _value = atol(_text.c_str());
      }
    };

  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXTEX_HPP__
