#include "UA.hpp"

#include "ApplicationDelegate.hpp"
#include "TransactionLayer.hpp"

#include "listeners/UAListener.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"
#include "protocol/SIPMessage.hpp"


using namespace sip0x;
using namespace sip0x::utils;

UA::UA(ApplicationDelegate* application_delegate, TransactionLayer* transaction, std::string domain, std::string useragent) :
  _application_delegate(application_delegate),
  _transaction(transaction),
  _domain(domain),
  _useragent(useragent) {

}

UA::~UA(void) {
}


void UA::add_listener(std::shared_ptr<listeners::UAListener>& listener) {
  _listeners.insert(listener);
}


void UA::remove_listener(std::shared_ptr<listeners::UAListener>& listener) {
  _listeners.erase(listener);
}


void UA::raise_listener(std::shared_ptr<Transaction>& tran, std::shared_ptr<protocol::SIPResponse>& response) {
  for (auto listener : _listeners) {
    listener->on_response(tran, response);
  }
}


//! \brief Add default header line. Ex: User agent, Max-Forwards, Via etc
void UA::add_default_header_lines(protocol::SIPMessage* message) {
  // Max-Forwards: 70
  std::shared_ptr<SIPMessageHeaderMax_Forwards> max_forward = std::make_shared<SIPMessageHeaderMax_Forwards>();
  max_forward->max = 70;
  message->headers.push_back(max_forward);

  std::shared_ptr<SIPMessageHeaderUser_Agent> user_agent = std::make_shared<SIPMessageHeaderUser_Agent>();
  user_agent->user_agent = _useragent;
  message->headers.push_back(user_agent);
}

void UA::add_header_cseq(protocol::SIPMessage* message, protocol::SIPMethod method, int seq) {
  std::shared_ptr<SIPMessageHeaderCSeq> cseq = std::make_shared<SIPMessageHeaderCSeq>();
  cseq->seq = seq;
  cseq->method = method;

  message->headers.push_back(cseq);
}


void UA::add_header_expires(protocol::SIPMessage* message, int expires) {
  std::shared_ptr<SIPMessageHeaderExpires> e = std::make_shared<SIPMessageHeaderExpires>();
  e->expires = expires;

  message->headers.push_back(e);
}


void UA::add_header_call_ID(protocol::SIPMessage* message, std::string const& callID) {
  std::shared_ptr<SIPMessageHeaderCall_ID> call_ID = std::make_shared<SIPMessageHeaderCall_ID>();
  call_ID->callID = callID;
  message->headers.push_back(call_ID);
}

void UA::add_header_via(protocol::SIPMessage* message, char const* transport, char const* branch) {
  // Via: SIP/2.0/UDP bobspc.biloxi.com:5060;branch=z9hG4bKnashds7
  std::shared_ptr<SIPMessageHeaderVia> via = std::make_shared<SIPMessageHeaderVia>();
  via->protocol = "SIP";
  via->version = "2.0";
  via->transport = transport; // TODO: Should be updated by the transport layer.
  via->hostport.host = _domain; // It should be the nat or local IP.
  via->params.push_back(std::make_pair("branch", branch)); // TODO: Implement a create branch.
  message->headers.push_back(via);

}

void UA::add_content(protocol::SIPMessage* message, uint8_t* content, std::size_t size) {
  // Content-Length: 0
  std::shared_ptr<SIPMessageHeaderContent_Length> content_length = std::make_shared<SIPMessageHeaderContent_Length>();
  content_length->length = size;
  message->headers.push_back(content_length);
        
  if (content != nullptr) {
    // TODO: Implements.
    //message->content = nullptr;
  }
}
