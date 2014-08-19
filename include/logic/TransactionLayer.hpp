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
#include "logic/TransportLayer.hpp"
#include "logic/TransportListener.hpp"

#include <set>

namespace sip0x
{
  namespace Logic
  {
    using namespace sip0x::Utils::Log;
    using namespace sip0x;

    //! \brief Provides handling and processing for bunch of Transaction.
    //! 
    //! Process REQUEST and RESPONSE. 
    class TransactionLayer : TransportRequestListener, TransportResponseListener {
    
    protected:
      std::shared_ptr<Logger> _logger;
      bool _act_has_server;
      // Listener
      TransactionListener* _listener;
      // Transactions.
      std::vector<Transaction*> _transactions;
      // Transport
      TransportLayer* _transport;

    public:
      TransactionLayer(TransactionListener* listener, TransportLayer* transport, bool act_has_server) :
          TransportRequestListener(), TransportResponseListener(),
          _act_has_server(act_has_server),
          _listener(listener), 
          _transport(transport) {
        _logger = LoggerManager::get_logger("sip0x.Logic.TransactionLayer");

        if (_act_has_server) {
          _transport->set_response_listener(this);
        }
        else {
          _transport->set_request_listener(this);
        }
      }

      virtual ~TransactionLayer(void) {
      }

      void handle(std::shared_ptr<SIPRequest>& request) {
        // Is a retransmission?
        Transaction* tran = create_transaction(request);
        
        if (!_act_has_server) {
          _transport->handle(request.get());
        }

        _listener->on_trying(tran);
      }

      void handle(SIPResponse* response) {

      }


      virtual void on_receive(std::shared_ptr<SIPRequest> request) override {
        if (_act_has_server) {
          // TODO: handling retransmission.
          Transaction* tran = create_transaction(request);
          // Notify the UA of the new transaction.
          _listener->on_trying(tran);
        }
        else {
          // TODO: This case should be ignored. Log dropping
        }
      }

      virtual void on_receive(std::shared_ptr<SIPResponse> response) override {

      }

    private:

      Transaction* create_transaction(std::shared_ptr<SIPRequest>& request) {
        Transaction* tran = new Transaction();
        tran->request = request;
        _transactions.push_back(tran);
        return tran;
      }
    };
  }
}

#endif // SIP0X_LOGIC_TRANSACTIONLAYER_HPP__
