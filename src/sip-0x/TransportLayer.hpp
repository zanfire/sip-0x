#if !defined(SIP0X_TRANSPORTLAYER_HPP__)
#define SIP0X_TRANSPORTLAYER_HPP__

#include <string>
#include <memory>

#include "utils/utils.hpp"

namespace sip0x
{
  class Transaction;

  namespace utils {
    class Logger;
  }

  namespace listeners {
    class TransportListener;
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

    listeners::TransportListener* _listener = nullptr;

  public:
    TransportLayer(void);
    virtual ~TransportLayer(void);

    void set_listener(listeners::TransportListener* l)  { _listener = l; }

    //! Send data to the lower layer (impl. dependent) like network or mock layer.
    virtual void send(std::shared_ptr<sip0x::Transaction>& transaction, std::shared_ptr<sip0x::protocol::SIPMessage> const& message) = 0;
    virtual void on_receive(std::shared_ptr<sip0x::protocol::SIPMessage> const& message) = 0;
  };
}

#endif // SIP0X_TRANSPORTLAYER_HPP__
