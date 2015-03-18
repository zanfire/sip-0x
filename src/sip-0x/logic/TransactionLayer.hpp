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

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

#include "logic/Transaction.hpp"
#include "logic/TransportLayer.hpp"
#include "logic/TransportListener.hpp"

#include <set>

namespace sip0x
{
  namespace Logic
  {
    using namespace sip0x::utils;
    using namespace sip0x;

    class TransactionLayerRequestListener {
    public:
      virtual void on_incoming_request(std::shared_ptr<Transaction>& tran, std::shared_ptr<SIPRequest>& request) {};
    };

    class TransactionLayerResponseListener {
    public:
      virtual void on_incoming_response(std::shared_ptr<Transaction>& tran, std::shared_ptr<SIPResponse>& response) {};
    };


    //! \brief Provides handling and processing for bunch of Transaction.
    //! 
    //! Process REQUEST and RESPONSE. 
    class TransactionLayer : TransportListener {
    
    protected:
      std::shared_ptr<Logger> _logger;
      // Listener
      TransactionLayerRequestListener* _listener_request;
      TransactionLayerResponseListener* _listener_response;
      // Transactions.
      std::unordered_map<std::string, std::shared_ptr<Transaction>> _transactions;
      // Transport
      TransportLayer* _transport;

    public:
      TransactionLayer(TransportLayer* transport) :
          TransportListener(),
          _transport(transport) {
        _logger = LoggerFactory::get_logger("sip0x.Logic.TransactionLayer");

        _transport->set_listener(this);
      }

      virtual ~TransactionLayer(void) {
      }

      void set_listener_request(TransactionLayerRequestListener* listener) {
        _listener_request = listener;
      }

      void set_listener_response(TransactionLayerResponseListener* listener) {
        _listener_response = listener;
      }

      virtual void on_receive(std::shared_ptr<SIPMessage>& message, std::shared_ptr<Connection> connection) override {
        if (message->is_request) {
          auto request = std::dynamic_pointer_cast<SIPRequest>(message);
          std::shared_ptr<Transaction> tran = get_transaction(message);
          if (tran == nullptr) {
            tran = create_transaction(request, connection, true);
          }
          if (tran != nullptr) {
            process_request(tran, request);
          }
          else {
            LOG_INFO(_logger, "Ignoring request, transaction not available");
          }
        }
        else {
          auto response = std::dynamic_pointer_cast<SIPResponse>(message);
          std::shared_ptr<Transaction> tran = get_transaction(message);
          if (tran != nullptr) {
            process_response(tran, response);
          }
          else {
            LOG_INFO(_logger, "Ignoring response, transaction not available");
          }
        }
      }

    private:

      void process_request(std::shared_ptr<Transaction> transaction, std::shared_ptr<SIPRequest>& request) {
        bool accepted = transaction->update_state_machine(request, false, false);
        if (accepted) {
          // TODO: handling retransmission.
          // Notify the UA of the new transaction.
          if (transaction->origin_remote) {
            _listener_request->on_incoming_request(transaction, request);
          }
          else {
            // Send to the NETWORK!!!
            _transport->send(transaction, request);
          }
        }
      }

      /*
      void process_response(std::shared_ptr<SIPResponse>& response, bool from_remote, void* opaque_data) {
        std::shared_ptr<Transaction> tran = get_transaction(response);
        if (tran != nullptr) {
          TransactionState prev_state = tran->state;
          bool accepted = tran->update_state_machine(response, false, false);
          if (accepted) {
            if (from_remote) {
              _listener_response->on_incoming_response(tran, response);
            }
            else {
              // Send to the NETWORK!!!
              _transport->send(response, opaque_data);
            }
          }
        }
      }
      */

      void process_response(std::shared_ptr<Transaction>& tran, std::shared_ptr<SIPResponse>& response) {
        if (tran != nullptr) {
          TransactionState prev_state = tran->state;
            bool accepted = tran->update_state_machine(response, false, false);
            if (accepted) {
            if (tran->origin_remote) {
              _listener_response->on_incoming_response(tran, response);
            }
            else {
              // Send to the NETWORK!!!
              _transport->send(response);
            }
          }
        }
      }

      //! Create a transaction.
      //! \param request The request that orgin the transaction.
      //! \param connection The TCP connection used to receive/send the transaction.
      //! \param origin_remote true if the origin of request is from a remote peer.
      std::shared_ptr<Transaction> create_transaction(std::shared_ptr<SIPRequest> const& request, std::shared_ptr<Connection> connection, bool origin_remote) {
        std::shared_ptr<Transaction> tran;
        //tran->request = request;
        // get from via the brach tag.
        std::string branch = request->get_Via_branch();
        if (!branch.empty()) {
          tran = std::make_shared<Transaction>();
          tran->origin_remote = origin_remote;
          tran->connection = connection;
          tran->id = sip0x::to_string(request->method) + "_" + branch;
          // TODO: Add check against present branch
          _transactions[tran->id] = tran;
        }
        else {
          LOG_INFO(_logger, "Tried to create a transaction with a incomplete/malformed request, ignoring request.");
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
