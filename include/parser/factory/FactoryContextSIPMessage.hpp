#if !defined(SIP0X_PARSER_FACTORYCONTEXTSIPMESSAGE_HPP__)
#define SIP0X_PARSER_FACTORYCONTEXTSIPMESSAGE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/factory/FactoryContextValue.hpp"

#include "protocol/SIP.hpp"

namespace Sip0x
{
  namespace Parser
  {
    using namespace Sip0x::Protocol;

    class FactoryContextSIPMessage : public FactoryContext {
    protected:
      bool _create_request = false;
      SIPRequest _request;
      SIPResponse _response;
    public:
      virtual void create(std::string const& text) override {
        if (_children.size() >= 3) {
          SIPMessage* message = nullptr;
          FactoryContextSIPMethod* method = dynamic_cast<FactoryContextSIPMethod*>(_children[0]);
          if (method != nullptr) {
            // It is a request
            _request.method = method->get();

            FactoryContextSIPURI* uri = dynamic_cast<FactoryContextSIPURI*>(_children[1]);
            if (uri != nullptr) {
              _request.uri = uri->get();
            }

            FactoryContextSIPVersion* version = dynamic_cast<FactoryContextSIPVersion*>(_children[2]);
            if (version != nullptr) {
              _request.version = version->get();
            }

            message = &_request;
            _create_request = true;
          }
          else {
            FactoryContextSIPVersion* version = dynamic_cast<FactoryContextSIPVersion*>(_children[0]);
            if (version != nullptr) {
              _response.version = version->get();
            }

            _response.status_code = atol(_children[1]->text().c_str());
            _response.reason_phrase = _children[2]->text();

            message = &_response;
          }

          unsigned int idx = 3;
          while (idx < _children.size()) {
            FactoryContextSIPMessageHeader* header = dynamic_cast<FactoryContextSIPMessageHeader*>(_children[idx]);
            if (header != nullptr) {
              message->headers.push_back(header->get());
            }
            else {
              break;
            }
            idx++;
          }

          // Get content...

          //for (auto c : _children) { delete c; }
          //_children.clear();
        }
      }

      bool is_request(void) { return _create_request; }
      SIPRequest& request(void) { return _request; }
      SIPResponse& response(void) { return _response; }
    };
  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXTSIPMESSAGE_HPP__
