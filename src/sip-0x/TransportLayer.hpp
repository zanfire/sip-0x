#if !defined(SIP0X_TRANSPORTLAYER_HPP__)
#define SIP0X_TRANSPORTLAYER_HPP__

#include <string>
#include <memory>

#include "RemotePeer.hpp"

#include "utils/utils.hpp"
#include "utils/Signals.hpp"

namespace sip0x
{
  class Transaction;

  namespace utils {
    class Logger;
  }

  namespace protocol {
    class SIPMessage;
  }

  //! Abstraction of Transport layer of SIP RFC.
  //!
  //! Derived classes are TransportLayerTCP and TransportLayerMock.
  class TransportLayer  {

  protected:
    std::shared_ptr<utils::Logger> _logger;
    std::shared_ptr<utils::Logger> _logger_siptrace;

  public:
    ///! Event of received message on specify remote peer.
    sip0x::utils::Signal<std::shared_ptr<sip0x::protocol::SIPMessage>&, std::shared_ptr<sip0x::RemotePeer>&> received;

  public:
    TransportLayer(void);
    virtual ~TransportLayer(void);

    //! Send data to the lower layer (impl. dependent) like network or mock layer.
    virtual void send(std::shared_ptr<sip0x::Transaction>& transaction, std::shared_ptr<const sip0x::protocol::SIPMessage>& message) = 0;
  };
}

#endif // SIP0X_TRANSPORTLAYER_HPP__
