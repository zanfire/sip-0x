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

#include "protocol/SIP.hpp"
#include "logic/Connection.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

#include <memory>

namespace sip0x
{
  namespace Logic
  {
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
      std::shared_ptr<sip0x::Utils::Logger> _logger;
      // TODO: Work on ID
    public:
      std::string id;
      //! Reference to the connection associated to this transaction.
      //! \remark This connection is not available for UDP scenario.
      std::shared_ptr<Connection> connection;
      //! True if the origin of this transaction is from remote.
      bool origin_remote = false;
      // State machine
      TransactionState state = TransactionState::TRANSACTION_STATE_UNKNOWN;
      std::shared_ptr<SIPRequest> request;
      std::shared_ptr<SIPResponse> response;

    public:
      Transaction(void) {
        _logger = sip0x::Utils::LoggerFactory::get_logger("sip0x.Logic.Transaction");
      }

      virtual ~Transaction(void) {
      }

      //! Update Transaction state machine.
      //! \arg tran is Transaction with updated by TransactionLayer.
      //! \arg message is new message processed.
      //! \arg timer_J is timer J for transaction termination.
      //! \arg transport_failure is a flag for transport failure.
      //! \returns true if message was accepted by state machine otherwise false.
      bool update_state_machine(std::shared_ptr<SIPMessage> const& message, bool timer_J, bool transport_failure) {
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
    };
  }
}

#endif // SIP0X_LOGIC_TRANSACTION_HPP__