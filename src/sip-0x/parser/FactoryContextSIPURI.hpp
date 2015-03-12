#if !defined(SIP0X_PARSER_FACTORYCONTEXTSIPURI_HPP__)
#define SIP0X_PARSER_FACTORYCONTEXTSIPURI_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/factory/FactoryContextValue.hpp"

#include "protocol/SIP.hpp"

namespace sip0x
{
  namespace Parser
  {
    using namespace sip0x;

    class FactoryContextUserInfo : public FactoryContextValue<SIPURI::UserInfo> {
    public:
      virtual void create(std::string const& /*text*/) override {
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
      virtual void create(std::string const& text) override {
        if (_children.size() == 3) {
          _value.param = _children[0]->text();
          _value.value = _children[2]->text();

          for (auto c : _children) { delete c; }
          _children.clear();
        }
      }
    };

    class FactoryContextURIParameters : public FactoryContextValue<std::vector<SIPURI::Param>> {
    public:
      virtual void create(std::string const& /*text*/) override {
        for (unsigned int i = 1; i < _children.size(); i++) {
          FactoryContextValue<SIPURI::Param>* fcv = dynamic_cast<FactoryContextValue<SIPURI::Param>*>(_children[i]);
          if (fcv != nullptr) {
            _value.push_back(fcv->get());
          }
        }

        for (auto c : _children) { delete c; }
        _children.clear();
      }
    };


    class FactoryContextHostPort : public FactoryContextValue<HostPort> {
    public:
      virtual void create(std::string const& /*text*/) override {
        std::size_t idx = 0;
        _value.host.clear();
        while (idx < _children.size()) {
          if (_children[idx]->text().compare(":") == 0) break;
          _value.host += _children[idx]->text();
          ++idx;
        }
        if (idx + 1 < _children.size()) {
          FactoryContextDigits* digits = dynamic_cast<FactoryContextDigits*>(_children[idx + 1]);
          if (digits != nullptr) {
            _value.port = digits->get();
          }
        }
        for (auto c : _children) { delete c; }
        _children.clear();
      }
    };

    class FactoryContextSIPURI : public FactoryContextValue<SIPURI> {
    public:
      virtual void create(std::string const& text) override {
        if (_children.size() >= 3) {
          _value.secure = _children[0]->text().compare("sips:") == 0;
          FactoryContextUserInfo* userinfo = dynamic_cast<FactoryContextUserInfo*>(_children[1]);
          if (userinfo != nullptr) {
            _value.userinfo = userinfo->get();
          }
          FactoryContextHostPort* hostport = dynamic_cast<FactoryContextHostPort*>(_children[2]);
          if (hostport != nullptr) {
            _value.hostport = hostport->get();
          }
        }
        if (_children.size() >= 4) {
          FactoryContextURIParameters* params = dynamic_cast<FactoryContextURIParameters*>(_children[3]);
          if (params != nullptr) {
            _value.uri_parameters = params->get();
          }
        }
        if (_children.size() >= 5) {
          FactoryContextURIParameters* params = dynamic_cast<FactoryContextURIParameters*>(_children[4]);
          if (params != nullptr) {
            _value.headers = params->get();
          }
        }
        for (auto c : _children) { delete c; }
        _children.clear();
      }
    };
  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXTSIPVERSION_HPP__
