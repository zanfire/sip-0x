#include "TransactionLayer.hpp"

#include "Transaction.hpp"
#include "TransportLayer.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"
#include "utils/Signals.hpp"
#include "protocol/SIPMessage.hpp"

#include <vector>

using namespace sip0x;
using namespace sip0x::utils;
using namespace sip0x::protocol;


TransactionLayer::TransactionLayer(std::shared_ptr<TransportLayer>& transport) : _transport(transport) {
  _logger = LoggerFactory::get_logger("sip0x.Logic.TransactionLayer");

  _slot.connect(this, &TransactionLayer::on_receive, _transport->received);
}

TransactionLayer::~TransactionLayer(void) {
}


void TransactionLayer::on_receive(std::shared_ptr<SIPMessage>& message, std::shared_ptr<RemotePeer>& remote) {
  if (message->is_request) {
    auto request = std::dynamic_pointer_cast<SIPRequest>(message);
    std::shared_ptr<Transaction> tran = get_transaction(message);
    if (tran == nullptr) {
      tran = create_transaction(request, remote, true);
    }
    if (tran != nullptr) {
      process_request(tran, request, false);
    }
    else {
      LOG_INFO(_logger, "Ignoring request, transaction not available");
    }
  }
  else {
    auto response = std::dynamic_pointer_cast<SIPResponse>(message);
    std::shared_ptr<Transaction> tran = get_transaction(message);
    if (tran != nullptr) {
      process_response(tran, response, false);
    }
    else {
      LOG_INFO(_logger, "Ignoring response, transaction not available");
    }
  }
}


void TransactionLayer::process_request(std::shared_ptr<Transaction>& transaction, std::shared_ptr<SIPRequest>& request, bool forward_to_transport) {
  bool accepted = transaction->on_message(std::dynamic_pointer_cast<const SIPMessage>(request), forward_to_transport);
  if (accepted) {
    // TODO: handling retransmission.
    // Notify the UA of the new transaction.
    if (transaction->origin_remote) {
      received_request.emit(transaction, std::dynamic_pointer_cast<const SIPRequest>(request));
    }
  }
  else {
    LOG_WARN(_logger, "Transaction@%p doesn't accept request@%p", transaction.get(), request.get());
  }
}


void TransactionLayer::process_response(std::shared_ptr<Transaction>& transaction, std::shared_ptr<SIPResponse>& response, bool forward_to_transport) {
  TransactionState prev_state = transaction->state;
  bool accepted = transaction->on_message(std::dynamic_pointer_cast<const SIPMessage>(response), forward_to_transport);
  if (accepted) {
    received_response.emit(transaction, std::dynamic_pointer_cast<const SIPResponse>(response));
  }
  else {
    LOG_WARN(_logger, "Transaction@%p doesn't accept request@%p", transaction.get(), response.get());
  }
}

//! Create a transaction.
//! \param request The request that orgin the transaction.
//! \param connection The TCP connection used to receive/send the transaction.
//! \param origin_remote true if the origin of request is from a remote peer.
std::shared_ptr<Transaction> TransactionLayer::create_transaction(std::shared_ptr<SIPRequest> const& request, std::shared_ptr<RemotePeer> remote, bool origin_remote) {
  std::shared_ptr<Transaction> tran;
  //tran->request = request;
  // get from via the brach tag.
  std::string branch = request->get_Via_branch();
  if (!branch.empty()) {
    tran = std::make_shared<Transaction>(_transport);
    tran->origin_remote = origin_remote;
    tran->remotepeer = remote;
    tran->id = sip0x::protocol::to_string(request->method) + "_" + branch;
    // TODO: Add check against present branch
    _transactions[tran->id] = tran;
  }
  else {
    LOG_INFO(_logger, "Tried to create a transaction with a incomplete/malformed request, ignoring request.");
  }
  return tran;
}

std::shared_ptr<Transaction> TransactionLayer::get_transaction(std::shared_ptr<SIPMessage> const& message) {
  std::shared_ptr<Transaction> tran;
  std::string branch = message->get_Via_branch();
  if (!branch.empty()) {
    std::string method;
    if (message->is_request) {
      SIPRequest const* req = dynamic_cast<SIPRequest const*>(message.get());
      method = sip0x::protocol::to_string(req->method);
    }
    else {
      std::shared_ptr<SIPMessageHeaderCSeq> cseq = message->get_first<SIPMessageHeaderCSeq>();
      if (cseq != nullptr) {
        method = sip0x::protocol::to_string(cseq->method);
      }
    }
    if (!method.empty()) {
      std::string id = method + "_" + branch;
      // TODO: Add check against present branch
      tran = _transactions[id];
    }
  }
  return tran; // correct or empty.
}


void TransactionLayer::on_process(void) {
  std::vector<std::string> vTransactionTerm;
  // Process timers and collect transaction states.
  for (auto t : _transactions) {
    t.second->process_timers();
    if (t.second->state == TransactionState::TRANSACTION_STATE_TERMINATED) {
      vTransactionTerm.push_back(t.first);
    }
  }

  // Remove terminated transaction.
  for (auto id : vTransactionTerm) {
    _transactions.erase(id);
  }
}