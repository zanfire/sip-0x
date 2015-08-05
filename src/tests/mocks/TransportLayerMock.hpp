#if !defined(SIP0X_TRANSPORTLAYERMOCK_HPP__)
#define SIP0X_TRANSPORTLAYERMOCK_HPP__

#include "TransportLayer.hpp"

namespace mocks
{
  //! Mock object for testing objected tied on transport.
  class TransportLayerMock : public sip0x::TransportLayer {
  protected:
    std::shared_ptr<const sip0x::protocol::SIPMessage> _last_message;

  public:
    TransportLayerMock(void);
    virtual ~TransportLayerMock(void);
  
    //! Inject message into the 
    void inject_message(uint8_t const* buffer, std::size_t size);
    std::shared_ptr<const sip0x::protocol::SIPMessage> get_last_message(void) { return _last_message; }


    virtual void send(const std::shared_ptr<sip0x::Transaction>& transaction, const std::shared_ptr<const sip0x::protocol::SIPMessage>& message) override;
  public:
  };
}

#endif // SIP0X_TRANSPORTLAYERMOCK_HPP__
