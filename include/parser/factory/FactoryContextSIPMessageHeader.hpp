#if !defined(SIP0X_PARSER_FACTORYCONTEXTSIPMSSAGEHEADER_HPP__)
#define SIP0X_PARSER_FACTORYCONTEXTSIPMSSAGEHEADER_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/factory/FactoryContextValue.hpp"

#include "protocol/SIP.hpp"

namespace Sip0x
{
  namespace Parser
  {
    using namespace Sip0x::Protocol;

    class FactoryContextSIPMessageHeader : public FactoryContextValue<SIPMessageHeader> {
    public:
      virtual void create(TokenAbstract const* token, ReadResult const& result) override {
        if (_children.size() == 3) {
          _value.name = _children[0]->text();
          _value.value = _children[2]->text();
          
          for (auto c : _children) { delete c; }
          _children.clear();
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXTSIPMSSAGEHEADER_HPP__
