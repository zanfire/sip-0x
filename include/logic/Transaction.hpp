#if !defined(SIP0X_LOGIC_TRANSACTION_HPP__)
#define SIP0X_LOGIC_TRANSACTION_HPP__

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

#include "protocol/SIP.hpp"

namespace sip0x
{
  namespace Logic
  {
    enum TransactionStatus {
      TRANSACTION_STATUS_TRYING,
      TRANSACTION_STATUS_PROCESSING,
      TRANSACTION_STATUS_COMPLETED,
      TRANSACTION_STATUS_TERMINATED,
    };

    //! A Transaction is a pair of Request and response
    struct Transaction {
      std::string id;
      TransactionStatus status;

      std::shared_ptr<SIPRequest> request;
      std::shared_ptr<SIPResponse> response;
    };

    //! \brief Transaction callbacks.
    class TransactionListener {
    public:
      virtual void on_trying(Transaction* tran) = 0;
      virtual void on_processing(Transaction* tran) = 0;
      virtual void on_completed(Transaction* tran) = 0;
      virtual void on_terminated(Transaction* tran) = 0;
    };
  }
}

#endif // SIP0X_LOGIC_TRANSACTION_HPP__