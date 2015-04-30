#include "protocol/SIPMessage.hpp"

#include <string>
#include <vector>
#include <ostream>

#include "protocol/SIPURI.hpp"
#include "protocol/SIPMethod.hpp"
#include "protocol/SIPVersion.hpp"

using namespace sip0x::protocol;

std::string SIPMessage::to_string(void) const {
  std::string out;
  for (auto h : headers) {
    out += h->to_string();
  }
  out += "\r\n";
  //for (auto c : content) {
  //  stream.put(c);
  //}
  return out;
}

std::string SIPMessage::get_Via_branch(void) const {
  std::shared_ptr<SIPMessageHeaderVia> via = get_first<SIPMessageHeaderVia>();
  if (via != nullptr) {
    for (auto param : via->params) {
      if (param.first.compare("branch") == 0) {
        return param.second;
      }
    }
  }
  return "";
}

SIPMessage* SIPMessage::clone(void) const {
  SIPMessage* c = impl_clone();
  for (auto h : headers) {
    std::shared_ptr<SIPMessageHeaderBase> ref(h->clone());
    c->headers.push_back(ref);
  }
  c->content = content;
  return c;
}

SIPRequest::SIPRequest(void) : SIPMessage() {
  is_request = true;
}

std::string SIPRequest::to_string(void) const {
  return sip0x::protocol::to_string(method) + ' ' + uri.to_string() + ' ' + version.to_string() + "\r\n" + SIPMessage::to_string();
}


SIPMessage* SIPRequest::impl_clone(void) const {
  SIPRequest* c = new SIPRequest();
  c->method = method;
  c->uri = uri;
  c->version = version;
  return c;
}

SIPResponse::SIPResponse(void) : SIPMessage() {
  is_request = false;
}


std::string SIPResponse::to_string(void) const {
  return version.to_string() + ' ' + std::to_string(status_code) + ' ' + reason_phrase + "\r\n" + SIPMessage::to_string();
}


SIPMessage* SIPResponse::impl_clone(void) const {
  SIPResponse* c = new SIPResponse();
  c->version = version;
  c->status_code = status_code;
  c->reason_phrase = reason_phrase;
  return c;
}
