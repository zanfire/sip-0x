#if !defined(SIP0X_PARSER_FACTORYCONTEXTSIPVERSION_HPP__)
#define SIP0X_PARSER_FACTORYCONTEXTSIPVERSION_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/factory/FactoryContextValue.hpp"

#include "protocol/SIP.hpp"

namespace Sip0x
{
  namespace Parser
  {
    using namespace Sip0x::Protocol;

    class FactoryContextSIPVersion : public FactoryContextBase<SIPVersion> {
    protected:
    public:
      virtual void create(TokenAbstract const* token, ReadResult const& result) override {
        if (_children.size() == 4) {
          _type.major = ((FactoryContextDigits*)_children[1])->get();
          _type.minor = ((FactoryContextDigits*)_children[3])->get();

          for (auto c : _children) { delete c; }
          _children.clear();
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXTSIPVERSION_HPP__
