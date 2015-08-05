#include "parser/factory/FactoryContextSIPMessage.hpp"

#include "parser/factory/FactoryContextValue.hpp"
#include "parser/factory/FactoryContextSIPURI.hpp"
#include "parser/factory/FactoryContextSIPVersion.hpp"
#include "parser/factory/FactoryContextSIPMessageHeader.hpp"

#include "protocol/SIP.hpp"

using namespace sip0x::parser;
using namespace sip0x::protocol;

void FactoryContextSIPMessage::impl_create(void) {
  if (_children.size() >= 3) {
    SIPMessage* message = nullptr;
    FactoryContextSIPMethod* method = dynamic_cast<FactoryContextSIPMethod*>(_children[0]);
    if (method != nullptr) {
      SIPRequest* request = new SIPRequest();
      // It is a request
      request->method = method->get();

      FactoryContextSIPURI* uri = dynamic_cast<FactoryContextSIPURI*>(_children[1]);
      if (uri != nullptr) {
        request->uri = uri->get();
      }

      FactoryContextSIPVersion* version = dynamic_cast<FactoryContextSIPVersion*>(_children[2]);
      if (version != nullptr) {
        request->version = version->get();
      }

      _message.reset(request);
    }
    else {
      SIPResponse* response = new SIPResponse();
      FactoryContextSIPVersion* version = dynamic_cast<FactoryContextSIPVersion*>(_children[0]);
      if (version != nullptr) {
        response->version = version->get();
      }

      response->status_code = atoi(_children[1]->text().c_str());
      response->reason_phrase = _children[2]->text();

      _message.reset(response);
    }

    unsigned int idx = 3;
    while (idx < _children.size()) {
      FactoryContextSIPMessageHeader* header = dynamic_cast<FactoryContextSIPMessageHeader*>(_children[idx]);
      if (header != nullptr) {
        _message->headers.push_back(header->get());
      }
      idx++;
    }
  }
}
