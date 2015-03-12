#if !defined(SIP0X_PARSER_FACTORYCONTEXTNAMEADDR_HPP__)
#define SIP0X_PARSER_FACTORYCONTEXTNAMEADDR_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/factory/FactoryContextValue.hpp"

#include "protocol/SIP.hpp"

namespace sip0x
{
  namespace Parser
  {
    using namespace sip0x;

    class FactoryContextNameAddr : public FactoryContextValue<NameAddr> {
    public:
      virtual void create(std::string const& text) override {
        int idx = 1;
        if (_children.size() == 4) {
          _value.displayName = _children[0]->text();
          idx = 2;
        }
        FactoryContextSIPURI* sipuri = dynamic_cast<FactoryContextSIPURI*>(_children[idx]);
        if (sipuri != nullptr) {
          _value.uri = sipuri->get();
        
          for (auto c : _children) { delete c; }
          _children.clear();
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXTNAMEADDR_HPP__
