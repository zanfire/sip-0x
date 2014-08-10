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

namespace Sip0x
{
  namespace Logic
  {
    using namespace Sip0x::Utils::Log;
    using namespace Sip0x;

    class Transaction;

    class TransactionListener {
      virtual void onCreated(Transaction* tran, SIPRequest* request) = 0;
      virtual void onTimedout(Transaction* tran) = 0;
      virtual void onCompleted(Transaction* tran, SIPResponse* response) = 0;
    };    
  }
}

#endif // SIP0X_LOGIC_TRANSACTIONLAYER_HPP__
