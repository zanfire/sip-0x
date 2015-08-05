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

#include "RemotePeer.hpp"
#include "utils/Signals.hpp"

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
  class TransactionLayer {
  protected:
    std::shared_ptr<utils::Logger> _logger;
    // Transactions.
    std::unordered_map<std::string, std::shared_ptr<Transaction>> _transactions;
    // Transport
    std::shared_ptr<TransportLayer> _transport;
    // Slot handler.
    utils::Slot _slot;

  public:  
    utils::Signal<const std::shared_ptr<sip0x::Transaction>&, const std::shared_ptr<const sip0x::protocol::SIPRequest>&> received_request;
    utils::Signal<const std::shared_ptr<sip0x::Transaction>&, const std::shared_ptr<const sip0x::protocol::SIPResponse>&> received_response;

  public:
    TransactionLayer(const std::shared_ptr<TransportLayer>& transport);
    virtual ~TransactionLayer(void);

    virtual void on_receive(const std::shared_ptr<sip0x::protocol::SIPMessage>& message, const std::shared_ptr<sip0x::RemotePeer>& connection);

    void process_request(const std::shared_ptr<Transaction>& transaction, const std::shared_ptr<sip0x::protocol::SIPRequest>& request, bool forward_to_transport);
    void process_response(const std::shared_ptr<Transaction>& transaction, const std::shared_ptr<sip0x::protocol::SIPResponse>& response, bool forward_to_transport);
      
    //! Create a transaction.
    //! \param request The request that orgin the transaction.
    //! \param connection The TCP connection used to receive/send the transaction.
    //! \param origin_remote true if the origin of request is from a remote peer.
    std::shared_ptr<Transaction> create_transaction(std::shared_ptr<sip0x::protocol::SIPRequest> const& request, std::shared_ptr<sip0x::RemotePeer> remote, bool origin_remote);
    
    std::shared_ptr<Transaction> get_transaction(const std::string& id);
    std::shared_ptr<Transaction> get_transaction(std::shared_ptr<sip0x::protocol::SIPMessage> const& message);

    //! Process timers for each transaction.
    void on_process(void);
  };
}

#endif // SIP0X_LOGIC_TRANSACTIONLAYER_HPP__
