#include "Transaction.hpp"

#include "protocol/SIPMessage.hpp"

#include "utils/Connection.hpp"
#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

#include <memory>

using namespace sip0x;
using namespace sip0x::utils;
using namespace sip0x::protocol;


Transaction::Transaction(void) {
  _logger = sip0x::utils::LoggerFactory::get_logger("sip0x.Logic.Transaction");
}


Transaction::~Transaction(void) {
}


bool Transaction::update_state_machine(std::shared_ptr<sip0x::protocol::SIPMessage> const& message, bool timer_J, bool transport_failure) {
  bool ret = false;
  TransactionState prev_state = state;
  switch (state)
  {
  case TransactionState::TRANSACTION_STATE_UNKNOWN:
  {
    // Unknown and message is a request of 
    // initialize transaction
    if (message->is_request) {
      state = TransactionState::TRANSACTION_STATE_TRYING;
      request = std::dynamic_pointer_cast<SIPRequest>(message);
      ret = true;
      LOG_DEBUG(_logger, "Transaction@%p go to TRANSACTION_STATE_TRYING state.");
    }
    else {
      LOG_ERROR(_logger, "Invalid message for state machine. Transaction wasn't initialized and transaction could not initialized with a non request message.");
    }
    break;
  }
  case TransactionState::TRANSACTION_STATE_TRYING:
  case TransactionState::TRANSACTION_STATE_PROCEEDING:
  {

    std::shared_ptr<SIPResponse> resp = std::dynamic_pointer_cast<SIPResponse>(message);
    if (resp != nullptr) {
      int code = resp->status_code;
      if (code >= 100 && code <= 199) {
        // From trying go to proceeding or confirm proceeding.
        state = TransactionState::TRANSACTION_STATE_PROCEEDING;
        ret = true;
        response = resp;
        LOG_DEBUG(_logger, "Transaction@%p go to TRANSACTION_STATE_PROCEEDING state.");
      }
      else if (code >= 200 && code <= 699) {
        // Transaction go to complete.
        state = TransactionState::TRANSACTION_STATE_COMPLETED;
        ret = true;
        response = resp;
        LOG_DEBUG(_logger, "Transaction@%p go to TRANSACTION_STATE_COMPLETED state.");
      }
      else {

      }

    }
    else {
      LOG_ERROR(_logger, "Invalid message for state machine.");
      ret = false;
    }
    break;
  }
  case TransactionState::TRANSACTION_STATE_COMPLETED:
  {
    // No message was accepted in this state.
    break;
  }
  case TransactionState::TRANSACTION_STATE_TERMINATED:
  {
    // No message was accepted in this state.
    break;
  }
  default:
    break;
  }
  // Trying
  // 1xx from TU send response go to Proceeding
  // Receive 200 - 699 go to Completed

  // Complete
  // Timer J go to Terminated

  if (prev_state != state) {
    // Logging for every cases
  }

  return ret;
}
