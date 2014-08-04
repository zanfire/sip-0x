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

    class FactoryContextSIPMessageHeader : public FactoryContextValue<std::shared_ptr<SIPMessageHeaderBase>> {
    public:
      virtual void create(TokenAbstract const* token, ReadResult const& result) override {
        if (_children.size() >= 1) {
          std::string param = _children[0]->text();
          if (param.compare("Call-ID") == 0) {
            SIPMessageHeaderCall_ID* h = new SIPMessageHeaderCall_ID();
            if (_children.size() == 3) {
              h->callID = _children[2]->text();
            }
            _value.reset(h);
          }
          else if(param.compare("Content-Length") == 0) {
            SIPMessageHeaderContent_Length* h = new SIPMessageHeaderContent_Length();
            extract_and_set_long(h->length);
            _value.reset(h);
          }
          else if (param.compare("CSeq") == 0) {
            SIPMessageHeaderCSeq* h = new SIPMessageHeaderCSeq();
            if (_children.size() == 5) {
              extract_and_set_long(h->seq);
              FactoryContextSIPMethod* method = dynamic_cast<FactoryContextSIPMethod*>(_children[4]);
              if (method != nullptr) {
                h->method = method->get();
              }
            }
            _value.reset(h);
          }
          else if (param.compare("Expires") == 0) {
            SIPMessageHeaderExpires* h = new SIPMessageHeaderExpires();
            extract_and_set_long(h->expires);
            _value.reset(h);
          }
          else if (param.compare("Max-Forwards") == 0) {
            SIPMessageHeaderMax_Forwards* h = new SIPMessageHeaderMax_Forwards();
            extract_and_set_long(h->max);
            _value.reset(h);
          }
          else if (param.compare("To") == 0) {
            SIPMessageHeaderCSeq* h = new SIPMessageHeaderCSeq();
            if (_children.size() == 5) {
              extract_and_set_long(h->seq);
              FactoryContextSIPMethod* method = dynamic_cast<FactoryContextSIPMethod*>(_children[4]);
              if (method != nullptr) {
                h->method = method->get();
              }
            }
            _value.reset(h);
          }
          else {
            SIPMessageHeaderGeneric* gen = new SIPMessageHeaderGeneric();
            gen->_name = param;
            if (_children.size() >= 3) {
              gen->_value = _children[2]->text();
            }
            _value.reset(gen);
          }

          for (auto c : _children) { delete c; }
          _children.clear();
        }
      }

      // SIPMessageHeaderMax_Forwards* h = new SIPMessageHeaderMax_Forwards();

      void extract_and_set_long(unsigned long &v) {
        if (_children.size() >= 3) {
          FactoryContextDigits* digit = dynamic_cast<FactoryContextDigits*>(_children[2]);
          if (digit != nullptr) {
            v = digit->get();
          }
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXTSIPMSSAGEHEADER_HPP__
