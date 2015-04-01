#include "UAC.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"


#include "Transaction.hpp"
#include "TransactionLayer.hpp"
#include "TransportLayer.hpp"
#include "protocol/SIPMessage.hpp"


using namespace sip0x;
using namespace sip0x::utils;

UAC::UAC(TransactionLayer* transaction, ApplicationDelegate* application_delegate, std::string domain, std::string useragent) 
    : UA(application_delegate, transaction, domain, useragent),
      listeners::TransactionLayerResponseListener(),
      _uniform_dist_Az('A', 'z') {

    // Seed with a real random value, if available
    std::random_device rd;
    _random_engine = std::default_random_engine(rd());

    _transaction->set_listener_response(this);
}


UAC::~UAC(void) {
}


void UAC::handle(std::shared_ptr<protocol::SIPRequest>& request) {
  // TODO: Create transaction was placed here to allow compilation, check if is it right!!!
  auto transaction = _transaction->create_transaction(request, nullptr, false);
  _transaction->process_request(transaction, request);
}


void UAC::on_incoming_response(std::shared_ptr<Transaction>& tran, std::shared_ptr<protocol::SIPResponse>& response) {
  raise_listener(tran, response);
}


std::shared_ptr<protocol::SIPRequest> UAC::create_REQUEST(std::string const& callID, protocol::SIPURI request_URI, protocol::SIPMethod method) {
  std::shared_ptr<protocol::SIPRequest> request = std::make_shared<protocol::SIPRequest>();
  request->method = method;
  request->version.major = 2;
  request->uri = request_URI;

  // Via: SIP/2.0/UDP bobspc.biloxi.com:5060;branch=z9hG4bKnashds7
  add_header_via(request.get(), "TCP", generate_branch().c_str());
  add_default_header_lines(request.get());
  add_header_cseq(request.get(), method, 1);
  add_header_call_ID(request.get(), callID);
  add_content(request.get(), nullptr, 0);

  return request;
}

//! Create a REGISTER request for this UAC.
std::shared_ptr<protocol::SIPRequest> UAC::create_REGISTER() {
  std::string callID = generate_CallID();
  protocol::SIPURI requestURI;
  requestURI.hostport.host = "requestURI@todo"; // TODO: Provide a parsing method for on the fly request.
  std::shared_ptr<protocol::SIPRequest> request = create_REQUEST(callID, requestURI, protocol::SIPMethod::SIPMETHOD_REGISTER);

  /*
  REGISTER sip:registrar.biloxi.com SIP/2.0
  Via: SIP/2.0/UDP bobspc.biloxi.com:5060;branch=z9hG4bKnashds7
  Max-Forwards: 70
  To: Bob <sip:bob@biloxi.com>
  Call-ID: 843817637684230@998sdasdh09
  From: Bob <sip:bob@biloxi.com>;tag=456248
  CSeq: 1826 REGISTER
  Contact: <sip:bob@192.0.2.4>
  Expires: 7200
  Content-Length: 0
  */

  // Add Expires header entry.
  // NOTO: Currently we place an header entry but we can update the Contact.
  std::shared_ptr<protocol::SIPMessageHeaderExpires> expires = std::make_shared<protocol::SIPMessageHeaderExpires>();
  expires->expires = 3;
  request->headers.push_back(expires);
  return request;
}

//! Generate a callID for this UAC.
std::string UAC::generate_CallID(void) {
  char buffer[16];

  buffer[sizeof(buffer) - 1] = 0x00;
  int idx = 0;
  while (idx < (sizeof(buffer) - 1)) {
    int value = _uniform_dist_Az(_random_engine);
    // Accept this value
    if ((value >= 'A' && value <= 'Z') || (value >= '0' && value <= '9') || (value >= 'a' && value <= 'z')) {
      buffer[idx] = (char)value;
      idx++;
    }
  }

  if (_domain.empty()) {
    return std::string(buffer);
  }
  else {
    return std::string(buffer) + '@' + _domain;
  }
}
   
std::string UAC::generate_branch(void) {
  char buffer[32];

  buffer[sizeof(buffer) - 1] = 0x00;
  int idx = 0;
  while (idx < (sizeof(buffer) - 1)) {
    int value = _uniform_dist_Az(_random_engine);
    // Accept this value
    if ((value >= 'A' && value <= 'Z') || (value >= '0' && value <= '9') || (value >= 'a' && value <= 'z')) {
      buffer[idx] = (char)value;
      idx++;
    }
  }

  return "z9hG4bK_" + std::string(buffer);
}
