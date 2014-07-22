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
    class FactoryContextBase : public FactoryContext {
    protected:
      T _type;
    public:

      T get(void) { return _type; }
    
    };

    

    class FactoryContextSIPMethod : public FactoryContextBase<SIPMethod> {
    protected:
    public:
      virtual void create(TokenAbstract const* token, ReadResult const& result) override {
        _type = convSIPMethodFromChars(result.parsed.c_str());
      }
    };

    class FactoryContextDigits : public FactoryContextBase<long> {
    protected:
    public:
      virtual void create(TokenAbstract const* token, ReadResult const& result) override {
        _type = atol(result.parsed.c_str());
      }
    };

  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXTEX_HPP__
