#if !defined(SIP0X_PARSER_FACTORYCONTEXTSIPURI_HPP__)
#define SIP0X_PARSER_FACTORYCONTEXTSIPURI_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/factory/FactoryContextValue.hpp"

#include "protocol/SIP.hpp"

namespace Sip0x
{
  namespace Parser
  {
    using namespace Sip0x::Protocol;

    class FactoryContextUserInfo : public FactoryContextValue<SIPURI::UserInfo> {
    public:
      virtual void create(TokenAbstract const* token, ReadResult const& result) override {
        if (_children.size() >= 2) {
          _value.username = _children[0]->text();
        }
        if (_children.size() >= 4) {
          _value.password = _children[2]->text();
        }
          
        for (auto c : _children) { delete c; }
        _children.clear();
      }
    };

    class FactoryContextURIParameter : public FactoryContextValue<SIPURI::Param> {
    public:
      virtual void create(TokenAbstract const* token, ReadResult const& result) override {
        if (_children.size() == 1) {
          FactoryContext* tmp = _children[0];
          _value.param = tmp->_children[0]->text();
          _value.value = tmp->_children[2]->text();


          for (auto c : _children) { delete c; }
          _children.clear();
        }
      }
    };

    class FactoryContextURIParameters : public FactoryContextValue<std::vector<SIPURI::Param>> {
    public:
      virtual void create(TokenAbstract const* token, ReadResult const& result) override {
        if (_children.size() >= 2) {
          SIPURI::Param param;
        }
      }
    };

    class FactoryContextSIPURI : public FactoryContextValue<SIPURI> {
    public:
      virtual void create(TokenAbstract const* token, ReadResult const& result) override {
        if (_children.size() >= 3) {
          _value.secure = _children[0]->text().compare("sips:") == 0;
          _value.userinfo = ((FactoryContextUserInfo*)_children[1])->get();
          _value.hostport.host = _children[2]->text();
          //_value.hostport - 
          //for (auto c : _children) { delete c; }
          //_children.clear();
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXTSIPVERSION_HPP__
