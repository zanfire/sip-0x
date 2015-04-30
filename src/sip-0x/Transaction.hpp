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

namespace sip0x
{
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
  class Transaction {
  protected:
    std::shared_ptr<sip0x::utils::Logger> _logger;
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

  public:
    Transaction(void);
    virtual ~Transaction(void);

    //! Update Transaction state machine.
    //! \arg tran is Transaction with updated by TransactionLayer.
    //! \arg message is new message processed.
    //! \arg timer_J is timer J for transaction termination.
    //! \arg transport_failure is a flag for transport failure.
    //! \returns true if message was accepted by state machine otherwise false.
    bool update_state_machine(std::shared_ptr<sip0x::protocol::SIPMessage> const& message, bool timer_J, bool transport_failure);
  };
}

#endif // SIP0X_LOGIC_TRANSACTION_HPP__