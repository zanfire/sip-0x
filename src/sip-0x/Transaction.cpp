#include "Transaction.hpp"

#include "TransportLayer.hpp"
#include "protocol/SIPMessage.hpp"

#include "utils/Connection.hpp"
#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

#include <memory>

using namespace sip0x;
using namespace sip0x::utils;
using namespace sip0x::protocol;

namespace t = std::chrono;

Transaction::Transaction(std::shared_ptr<sip0x::TransportLayer>& tran) : _transport(tran) {
  _logger = sip0x::utils::LoggerFactory::get_logger("sip0x.Transaction");
}


Transaction::~Transaction(void) {
}


bool Transaction::on_message(std::shared_ptr<sip0x::protocol::SIPMessage> const& message, bool forward) {
  std::lock_guard<std::recursive_mutex> guard(_mtx);

  if (state == TransactionState::TRANSACTION_STATE_COMPLETED || state == TransactionState::TRANSACTION_STATE_TERMINATED) {
    LOG_INFO(_logger, "%s: Ignore message because it was in COMPLETED or TERMINATED state.", to_string().c_str());
    return false;
  }
  bool ret = false;
  TransactionState prev_state = state;
  if (state == TransactionState::TRANSACTION_STATE_UNKNOWN) {
    // initialize transaction
    if (message->is_request) {
      // Initializing timer.
      _T0 = t::steady_clock::now();
      update_timers_value();
      LOG_DEBUG(_logger, "%s: set as T0 ref %lld ms.", to_string().c_str(), t::duration_cast<t::seconds>(_T0.time_since_epoch()).count());
      change_state(TransactionState::TRANSACTION_STATE_TRYING);
      request = std::dynamic_pointer_cast<SIPRequest>(message);
      if (forward) {
        _transport->send(shared_from_this(), message);
      }     
      return true;
    }
    else {
      LOG_ERROR(_logger, "%s: Invalid message for state machine. Transaction wasn't initialized and transaction could not initialized with a non request message.", to_string().c_str());
      return false;
    }
  }
  if (state == TransactionState::TRANSACTION_STATE_TRYING || state == TransactionState::TRANSACTION_STATE_PROCEEDING) {

    std::shared_ptr<SIPResponse> resp = std::dynamic_pointer_cast<SIPResponse>(message);
    if (resp != nullptr) {
      int code = resp->status_code;
      if (code >= 100 && code <= 199) {
        // From trying go to proceeding or confirm proceeding.
        change_state(TransactionState::TRANSACTION_STATE_PROCEEDING);
        response = resp;
        if (forward) {
          _transport->send(shared_from_this(), message);
        }
        return true;
      }
      else if (code >= 200 && code <= 699) {
        // Transaction go to complete.
        change_state(TransactionState::TRANSACTION_STATE_COMPLETED);
        response = resp;
        if (forward) {
          _transport->send(shared_from_this(), message);
        }
        return true;
      }
    }
  }

  LOG_DEBUG(_logger, "%s: SIP message was ignored because wasn't handled by transaction.", to_string().c_str());
  return false;
}


void Transaction::process_timers(void) {
  std::lock_guard<std::recursive_mutex> guard(_mtx);

  if (state == TransactionState::TRANSACTION_STATE_TERMINATED) {
    // Transaction is in the last state. it cannot change in this state and in awhile could be destroyed.
    return;
  }
  // refresh registration if it's time
  auto elapsed_secs = t::duration_cast<t::milliseconds>(t::steady_clock::now() - _T0);

  // Check if fire a timer event.
  if (is_udp() && is_INVITE() && elapsed_secs.count() >= _TimerA_secs) {
    // Timer A  initially T1     Section 17.1.1.2     INVITE request retransmit interval, for UDP only 
    LOG_DEBUG(_logger, "Timer A elapsed.");
  }
  if (is_INVITE() && elapsed_secs.count() >= _TimerB_secs) {
    // Timer B  64*T1            Section 17.1.1.2     INVITE transaction timeout timer 
    LOG_DEBUG(_logger, "Timer B elapsed.");
  }
  if (is_INVITE() && elapsed_secs.count() >= _TimerC_secs) {
    // Timer C  > 3min           Section 16.6         proxy INVITE transaction bullet 11 timeout 
    LOG_DEBUG(_logger, "Timer C elapsed.");
  }
  if (is_udp() && is_INVITE() && elapsed_secs.count() >= _TimerD_secs) {
    // Timer D  > 32s for UDP    Section 17.1.1.2     Wait time for response retransmits 
    //          0s for TCP/SCTP
    LOG_DEBUG(_logger, "Timer D elapsed.");
  }
  if (is_udp() && !is_INVITE() && elapsed_secs.count() >= _TimerE_secs) {
    // Timer E  initially T1     Section 17.1.2.2     non-INVITE request retransmit interval, UDP only 
    LOG_DEBUG(_logger, "Timer E elapsed.");
  }
  if (!is_INVITE() && elapsed_secs.count() >= _TimerF_secs && state < TransactionState::TRANSACTION_STATE_COMPLETED) {
    LOG_DEBUG(_logger, "%s: Timer F elapsed. This transaction will be terminated.", to_string().c_str());
    terminate();
  }
  if (is_INVITE() && elapsed_secs.count() >= _TimerG_secs) {
    // Timer G  initially T1     Section 17.2.1       INVITE response retransmit interval
    LOG_DEBUG(_logger, "Timer G elapsed.");
  }
  if (is_INVITE() && elapsed_secs.count() >= _TimerH_secs) {
    // Timer H  64*T1            Section 17.2.1       Wait time for ACK receipt 
    LOG_DEBUG(_logger, "Timer H elapsed.");
  }
  if (is_udp() && is_INVITE() && elapsed_secs.count() >= _TimerI_secs) {
    // Timer I  T4 for UDP       Section 17.2.1       Wait time for ACK retransmits 
    //          0s for TCP/SCTP
    LOG_DEBUG(_logger, "Timer I elapsed.");
  }
  if (is_udp() && !is_INVITE() && elapsed_secs.count() >= _TimerJ_secs &&  state == TransactionState::TRANSACTION_STATE_COMPLETED) {
    // Timer J  64*T1 for UDP    Section 17.2.2       Wait time for non-INVITE request retransmits 
    //          0s for TCP/SCTP
    LOG_DEBUG(_logger, "%s: Timer J elapsed, transaction is going to the terminated state.", to_string().c_str());
    terminate();
  }
  if (/*!is_udp() ??*/ !is_INVITE() && elapsed_secs.count() >= _TimerK_secs && state == TransactionState::TRANSACTION_STATE_COMPLETED) {
    LOG_DEBUG(_logger, "%s: Timer K elapsed, transaction is going to the terminated state.", to_string().c_str());
    terminate();
  }
}

void Transaction::terminate(void)  {
  LOG_DEBUG(_logger, "%s: Terminate transaction.", to_string().c_str());

  change_state(TransactionState::TRANSACTION_STATE_TERMINATED);
}


void Transaction::resend(void) {
  if (state == TransactionState::TRANSACTION_STATE_TRYING) {
    _transport->send(shared_from_this(), request);
  }
  else {
    // Ignoring 
  }
}

bool Transaction::is_udp(void) const {
  // This is wrong, the connection could be created only when we need to send data 
  // band after that they could be closed. Add implementation for detecting the right protocol.
  //return connection == nullptr;
  return false;
}


bool Transaction::is_INVITE(void) const {
  if (request != nullptr) {
    return request->method == SIPMethod::SIPMETHOD_INVITE;
  }
  return false;
}


void Transaction::update_timers_value(void) {
  _TimerA_secs = (long long)((_T1_rtti_ms * 1000) / 1000);
  _TimerB_secs = (long long)((_T1_rtti_ms * 1000 * 64) / 1000);
  _TimerC_secs = (long long)((_T1_rtti_ms * 1000 * 60 * 3) / 1000); // See documentations
  _TimerD_secs = (long long)((is_udp() ? _T1_rtti_ms * 1000 * 32 : 0) / 1000);
  _TimerE_secs = (long long)((_T1_rtti_ms * 1000) / 1000);
  _TimerF_secs = (long long)((_T1_rtti_ms * 1000 * 64) / 1000);
  _TimerG_secs = (long long)((_T1_rtti_ms * 1000) / 1000);
  _TimerH_secs = (long long)((_T1_rtti_ms * 1000 * 64) / 1000);
  _TimerI_secs = (long long)((is_udp() ? _T4_TTL_secs : 0) / 1000);
  _TimerJ_secs = (long long)((is_udp() ? _T1_rtti_ms * 1000 * 64 : 0) / 1000);
  _TimerK_secs = (long long)((is_udp() ? _T4_TTL_secs : 0) / 1000);
}


bool Transaction::change_state(TransactionState new_state) {
  std::lock_guard<std::recursive_mutex> guard(_mtx);

  if (new_state < state) {
    LOG_ERROR(_logger, "%s: Change state could not performed , requested %s -> %s.", to_string().c_str(), to_string(state), to_string(new_state));
    return false;
  }
  else if(new_state == state) {
    // Ignored, the same state requested.
    LOG_DEBUG(_logger, "%s: Ignoring change state %s -> %s.", to_string().c_str(), to_string(state), to_string(new_state));
    return true;
  }
  else if (new_state > state) {
    LOG_DEBUG(_logger, "%s: Change state %s -> %s.", to_string().c_str(), to_string(state), to_string(new_state));
    state = new_state;
    return true;
  }
  return false;
}

std::string Transaction::to_string(void) const {
  char buf[128];
  sprintf_s(buf, "Transaction@%p", this);
  return std::string(buf);
}

char const* Transaction::to_string(TransactionState state) {
  if (state == TransactionState::TRANSACTION_STATE_UNKNOWN)    return "TRANSACTION_STATE_UNKNOWN";
  if (state == TransactionState::TRANSACTION_STATE_TRYING)     return "TRANSACTION_STATE_TRYING";
  if (state == TransactionState::TRANSACTION_STATE_PROCEEDING) return "TRANSACTION_STATE_PROCEEDING";
  if (state == TransactionState::TRANSACTION_STATE_COMPLETED)  return "TRANSACTION_STATE_COMPLETED";
  if (state == TransactionState::TRANSACTION_STATE_TERMINATED) return "TRANSACTION_STATE_TERMINATED";
  return "??";
}
