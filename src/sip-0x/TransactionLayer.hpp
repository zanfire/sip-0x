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

#include <unordered_map>
#include <memory>
#include <string>

#include "listeners/TransportListener.hpp"

namespace sip0x
{
  class Transaction;
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

  namespace listeners {
    class TransactionLayerRequestListener;
    class TransactionLayerResponseListener;
  }
    

  //! \brief Provides handling and processing for bunch of Transaction.
  //! 
  //! Process REQUEST and RESPONSE. 
  class TransactionLayer : public sip0x::listeners::TransportListener {
  protected:
    std::shared_ptr<utils::Logger> _logger;
    // Listener
    listeners::TransactionLayerRequestListener* _listener_request;
    listeners::TransactionLayerResponseListener* _listener_response;
    // Transactions.
    std::unordered_map<std::string, std::shared_ptr<Transaction>> _transactions;
    // Transport
    std::shared_ptr<TransportLayer> _transport;

  public:
    TransactionLayer(std::shared_ptr<TransportLayer>& transport);
    virtual ~TransactionLayer(void);

    void set_listener_request(listeners::TransactionLayerRequestListener* listener) { _listener_request = listener; }
    void set_listener_response(listeners::TransactionLayerResponseListener* listener) { _listener_response = listener; }

    // TODO: Move to protected/private?
    virtual void on_receive(std::shared_ptr<sip0x::protocol::SIPMessage>& message, std::shared_ptr<sip0x::utils::Connection>& connection) override;

    void process_request(std::shared_ptr<Transaction>& transaction, std::shared_ptr<sip0x::protocol::SIPRequest>& request, bool forward_to_transport);
    void process_response(std::shared_ptr<Transaction>& transaction, std::shared_ptr<sip0x::protocol::SIPResponse>& response, bool forward_to_transport);
      
    //! Create a transaction.
    //! \param request The request that orgin the transaction.
    //! \param connection The TCP connection used to receive/send the transaction.
    //! \param origin_remote true if the origin of request is from a remote peer.
    std::shared_ptr<Transaction> create_transaction(std::shared_ptr<sip0x::protocol::SIPRequest> const& request, std::shared_ptr<sip0x::utils::Connection> connection, bool origin_remote);
      
    std::shared_ptr<Transaction> get_transaction(std::shared_ptr<sip0x::protocol::SIPMessage> const& message);
  };
}

#endif // SIP0X_LOGIC_TRANSACTIONLAYER_HPP__
