#include "UAS.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"
#include "Transaction.hpp"
#include "TransactionLayer.hpp"
#include "ApplicationDelegate.hpp"
#include "protocol/SIPMessage.hpp"

using namespace sip0x;
using namespace sip0x::protocol;
using namespace sip0x::utils;

UAS::UAS(TransactionLayer* transaction, ApplicationDelegate* application_delegate, std::string domain, std::string useragent) :
  UA(application_delegate, transaction, domain, useragent),
  TransactionLayerRequestListener() {
  _logger = LoggerFactory::get_logger("sip0x.Logic.UAS");

  _transaction->set_listener_request(this);
}

UAS::~UAS(void) {
}

void UAS::on_incoming_request(std::shared_ptr<Transaction>& tran, std::shared_ptr<SIPRequest>& request) {
  switch (request->method) {
    case SIPMethod::SIPMETHOD_REGISTER:
    {
      process_REGISTER(tran);
      break;
    }

  }
}

void UAS::process_REGISTER(std::shared_ptr<Transaction>& transaction) {
  // TODO: process and notify the Application of the register method.

  // Ask to the application layer if accept register from client

  bool accepted = _application_delegate->raise_cb_registrar_update(transaction->request);
  if (accepted) {
    // Create a valid response.
    std::shared_ptr<SIPResponse> response = create_RESPONSE_for(transaction->request.get(), 200, "OK");

    //
    int expires = _application_delegate->raise_cb_registrar_get_expires(transaction->request);
    if (expires >= 0) {
      add_header_expires(response.get(), expires);
    }

    _transaction->process_response(transaction, response, true);
    return;
  }
  else {
    // Create a reject response
  }

  // Create reject
  // Create a valid response.
  std::shared_ptr<SIPResponse> response = create_RESPONSE_for(transaction->request.get(), 500, "Server error");
  _transaction->process_response(transaction, response, true);
}


std::shared_ptr<SIPResponse> UAS::create_RESPONSE_for(SIPRequest* request, int code, char const* phrase) {
  std::shared_ptr<SIPResponse> response = std::make_shared<SIPResponse>();
  response->status_code = code;
  response->reason_phrase = phrase;
  response->version.major = 2;
        
  add_default_header_lines(response.get());
  std::shared_ptr<SIPMessageHeaderCall_ID> callID = request->get_first<SIPMessageHeaderCall_ID>();
  response->headers.push_back(callID);
        
  add_header_via(response.get(), "TCP", request->get_Via_branch().c_str());
  add_header_cseq(response.get(), request->method, 1);

  add_content(response.get(), nullptr, 0);

  return response;
}
