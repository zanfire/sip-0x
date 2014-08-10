#if !defined(SIP0X_LOGIC_TRANSACTIONLAYER_HPP__)
#define SIP0X_LOGIC_TRANSACTIONLAYER_HPP__

//!
//! Copyright 2014 Matteo Valdina
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

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"
#include "logic/Transaction.hpp"

#include <set>

namespace Sip0x
{
  namespace Logic
  {
    using namespace Sip0x::Utils::Log;
    using namespace Sip0x;

    //! \brief Provides handling and processfor bunch of Transaction.
    //! 
    //! Process REQUEST and RESPONSE. 
    class TransactionLayer {
    
    protected:
      std::shared_ptr<Logger> _logger;

      // Listener
      TransactionListener* _listener;

      // Transactions.
      std::set<Transaction> _transactions;

    public:
      TransactionLayer(TransactionListener* listener) : _listener(listener) {
        _logger = LoggerManager::get_logger("Sip0x.Logic.Transaction");
      }

      virtual ~TransactionLayer(void) {
      }

      void process(SIPRequest* request) {
        // Look in transaction set.
        // Create a transaction.

        // Process

        // After that i need to decide if give then to the trasport layer or
        // give to the UAS.
        // This depends if it is from 

        // Could by nice if each transaction is handled by the UAC or UAS?
      }

      void process(SIPResponse* response) {

      }
    };
  }
}

#endif // SIP0X_LOGIC_TRANSACTIONLAYER_HPP__
