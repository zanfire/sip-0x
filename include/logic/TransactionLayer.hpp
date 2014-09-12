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

    class TransactionLayerListener {
    public:
      virtual void on_incoming_request(std::shared_ptr<Transaction> tran, std::shared_ptr<SIPRequest>& request) {};
      virtual void on_incoming_response(std::shared_ptr<Transaction> tran, std::shared_ptr<SIPResponse>& response) {};
    };


    //! \brief Provides handling and processing for bunch of Transaction.
    //! 
    //! Process REQUEST and RESPONSE. 
    class TransactionLayer : TransportListener {
    
    protected:
      std::shared_ptr<Logger> _logger;
      bool _act_has_server;
      // Listener
      TransactionLayerListener* _listener;
      // Transactions.
      std::unordered_map<std::string, std::shared_ptr<Transaction>> _transactions;
      // Transport
      TransportLayer* _transport;

    public:
      TransactionLayer(TransactionLayerListener* listener, TransportLayer* transport, bool act_has_server) :
          TransportListener(),
          _act_has_server(act_has_server),
          _listener(listener), 
          _transport(transport) {
        _logger = LoggerManager::get_logger("sip0x.Logic.TransactionLayer");

        _transport->set_listener(this);
      }

      virtual ~TransactionLayer(void) {
      }


      virtual void on_receive(std::shared_ptr<SIPMessage>& message, void* opaque_data) override {
        if (message->is_request) {
          std::shared_ptr<SIPRequest> request = std::dynamic_pointer_cast<SIPRequest>(message);
          process_request(request, true, opaque_data);
        }
        else {
          std::shared_ptr<SIPResponse> response = std::dynamic_pointer_cast<SIPResponse>(message);
          process_response(response, true, opaque_data);
        }
      }

      virtual void process_request(std::shared_ptr<SIPRequest>& request, bool from_remote, void* opaque_data) {
        std::shared_ptr<Transaction> tran = get_transaction(request);
        if (tran != nullptr) {
          // is it a retransmission?
        }
        else {
          tran = create_transaction(request);
        }
        bool accepted = tran->update_state_machine(request, false, false);
        if (accepted) {
          tran->opaque_data = opaque_data; // Ugly hack !!!!!
          // TODO: handling retransmission.
          // Notify the UA of the new transaction.
          if (from_remote) {
            _listener->on_incoming_request(tran, request);
          }
          else {
            // Send to the NETWORK!!!
            _transport->send(request, opaque_data);
          }
        }
      }

      void process_response(std::shared_ptr<SIPResponse>& response, bool from_remote, void* opaque_data) {
        std::shared_ptr<Transaction> tran = get_transaction(response);
        if (tran != nullptr) {
          TransactionState prev_state = tran->state;
            bool accepted = tran->update_state_machine(response, false, false);
            if (accepted) {
            if (from_remote) {
              _listener->on_incoming_response(tran, response);
            }
            else {
              // Send to the NETWORK!!!
              _transport->send(response, opaque_data);
            }
          }
        }
      }


    private:

      std::shared_ptr<Transaction> create_transaction(std::shared_ptr<SIPRequest> const& request) {
        std::shared_ptr<Transaction> tran;
        //tran->request = request;
        // get from via the brach tag.
        std::string branch = request->get_Via_branch();
        if (!branch.empty()) {
          tran = std::make_shared<Transaction>();
          tran->id = sip0x::to_string(request->method) + "_" + branch;
          // TODO: Add check against present branch
          _transactions[tran->id] = tran;
        }
        else {
          // TODO: Add logging.
        }
        return tran;
      }

      std::shared_ptr<Transaction> get_transaction(std::shared_ptr<SIPMessage> const& message) {
        std::shared_ptr<Transaction> tran;
        std::string branch = message->get_Via_branch();
        if (!branch.empty()) {
          std::string method;
          if (message->is_request) {
            SIPRequest const* req = dynamic_cast<SIPRequest const*>(message.get());
            method = sip0x::to_string(req->method);
          }
          else {
            std::shared_ptr<SIPMessageHeaderCSeq> cseq = message->get_first<SIPMessageHeaderCSeq>();
            if (cseq != nullptr) {
              method = sip0x::to_string(cseq->method);
            }
          }
          if (!method.empty()) {
            std::string id = method + "_" + branch;
            // TODO: Add check against present branch
            tran = _transactions[id];
          }
        }
        return tran; // correct or empty.
      }
    };
  }
}

#endif // SIP0X_LOGIC_TRANSACTIONLAYER_HPP__
