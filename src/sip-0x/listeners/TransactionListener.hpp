#if !defined(SIP0X_LOGIC_TRANSACTIONLISTENER_HPP__)
#define SIP0X_LOGIC_TRANSACTIONLISTENER_HPP__

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

#include <memory>

namespace sip0x
{
  class Transaction;

  namespace protocol {
    class SIPRequest;
    class SIPResponse;
  }

  namespace listeners
  {
    class TransactionLayerRequestListener {
    public:
      virtual void on_incoming_request(std::shared_ptr<sip0x::Transaction>& tran, std::shared_ptr<sip0x::protocol::SIPRequest>& request) = 0;
    };

    class TransactionLayerResponseListener {
    public:
      virtual void on_incoming_response(std::shared_ptr<sip0x::Transaction>& tran, std::shared_ptr<sip0x::protocol::SIPResponse>& response) = 0;
    };
  }
}

#endif // SIP0X_LOGIC_TRANSACTIONLISTENER_HPP__