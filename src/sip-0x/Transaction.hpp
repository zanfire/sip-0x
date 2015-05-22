#if !defined(SIP0X_LOGIC_TRANSACTION_HPP__)
#define SIP0X_LOGIC_TRANSACTION_HPP__

//!
//! Copyright 2014-2015 Matteo Valdina
//!
//! Licensed under the Apache License, Version 2.0 (the "License");
//! you may not use this file except in compliance with the License.
//! You may obtain a copy of the License at
//!
//!     http://www.apache.org/licenses/LICENSE-2.0
//!
//! Unless required by applicable law or agreed to in writing, software
//! distributed under the License is distributed on an "AS IS" BASIS,
//! WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//! See the License for the specific language governing permissions and
//! limitations under the License.
//!

#include <memory>
#include <string>
#include <chrono>
#include <mutex>

/* 
  Documentation from RFC 3261

  Timer    Value            Section               Meaning 
  ---------------------------------------------------------------------
  T1       500ms default    Section 17.1.1.1     RTT Estimate 
  T2       4s               Section 17.1.2.2     The maximum retransmit interval for non-INVITE requests and INVITE responses
  T4       5s               Section 17.1.2.2     Maximum duration a message will remain in the network 
  Timer A  initially T1     Section 17.1.1.2     INVITE request retransmit interval, for UDP only 
  Timer B  64*T1            Section 17.1.1.2     INVITE transaction timeout timer 
  Timer C  > 3min           Section 16.6         proxy INVITE transaction bullet 11 timeout 
  Timer D  > 32s for UDP    Section 17.1.1.2     Wait time for response retransmits 
           0s for TCP/SCTP
  Timer E  initially T1     Section 17.1.2.2     non-INVITE request retransmit interval, UDP only 
  Timer F  64*T1            Section 17.1.2.2     non-INVITE transaction timeout timer 
  Timer G  initially T1     Section 17.2.1       INVITE response retransmit interval
  Timer H  64*T1            Section 17.2.1       Wait time for ACK receipt 
  Timer I  T4 for UDP       Section 17.2.1       Wait time for ACK retransmits 
           0s for TCP/SCTP
  Timer J  64*T1 for UDP    Section 17.2.2       Wait time for non-INVITE request retransmits 
           0s for TCP/SCTP
  Timer K  T4 for UDP       Section 17.1.2.2     Wait time for response retransmits
           0s for TCP/SCTP
*/

namespace sip0x
{
  class TransportLayer;

  namespace utils {
    class Logger;
    class Connection;
  }
  namespace protocol {
    class SIPMessage;
    class SIPRequest;
    class SIPResponse;
  }

  enum TransactionState {
    TRANSACTION_STATE_UNKNOWN = 0,
    TRANSACTION_STATE_TRYING = 1,
    TRANSACTION_STATE_PROCEEDING,
    TRANSACTION_STATE_COMPLETED,
    TRANSACTION_STATE_TERMINATED,
  };

    
  //! A Transaction is a pair of Request and response
  class Transaction : public std::enable_shared_from_this<Transaction> {
  protected:
    std::shared_ptr<sip0x::utils::Logger> _logger;
    std::recursive_mutex _mtx;
    std::shared_ptr<TransportLayer> _transport;
    // TODO: Work on ID
  public:
    std::string id;
    //! Reference to the connection associated to this transaction.
    //! \remark This connection is not available for UDP scenario.
    std::shared_ptr<utils::Connection> connection;
    //! True if the origin of this transaction is from remote.
    bool origin_remote = false;
    // State machine
    TransactionState state = TransactionState::TRANSACTION_STATE_UNKNOWN;
    std::shared_ptr<sip0x::protocol::SIPRequest> request;
    std::shared_ptr<sip0x::protocol::SIPResponse> response;
  
  protected:
    //! Time point of first request sent/received. Every computation are get as delta from this time.
    std::chrono::steady_clock::time_point _T0;

    // Timers ([timer name]_[description]_[units])
    long long const _T1_rtti_ms = 500;
    long long const _T2_maximum_retransmit_interval_secs = 4;
    long long const _T4_TTL_secs = 5;
    long long _TimerA_secs = 0;
    long long _TimerB_secs = 0;
    long long _TimerC_secs = 0;
    long long _TimerD_secs = 0;
    long long _TimerE_secs = 0;
    long long _TimerF_secs = 0;
    long long _TimerG_secs = 0;
    long long _TimerH_secs = 0;
    long long _TimerI_secs = 0;
    long long _TimerJ_secs = 0;
    long long _TimerK_secs = 0;


  public:
    Transaction(std::shared_ptr<TransportLayer>& transport);
    virtual ~Transaction(void);

    //! Update Transaction state machine.
    //! \arg message is the message dispatched to transaction.
    //! \arg forward mean that this message must be forwarded to the transport layer.
    //! \returns true if message was accepted by state machine otherwise false.
    bool on_message(std::shared_ptr<sip0x::protocol::SIPMessage> const& message, bool forward);
    //! Evaluate all timers for this transaction.
    void process_timers(void);

    //! \returns true if this message was sent/recv on UDP.
    bool is_udp(void) const;
    //! \returns true if it is a INVITE transaction.
    bool is_INVITE(void) const;

    std::string to_string(void) const;

    //! Statics
    static char const* to_string(TransactionState state);
  protected:
    //! Resend
    void resend(void);
    //! Terminate this transaction.
    void terminate(void);

    //! Changes the current state.
    //! \returns true if the state was accepted.
    bool change_state(TransactionState new_state);
    //! Update timers value in base of T0 and kind of transaction (non-INVITE, INVITE).
    void update_timers_value(void);
  };
}

#endif // SIP0X_LOGIC_TRANSACTION_HPP__