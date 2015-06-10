#if !defined(SIP0X_TRANSPORTLAYERMOCK_HPP__)
#define SIP0X_TRANSPORTLAYERMOCK_HPP__

#include "TransportLayer.hpp"

#include <string>

namespace mocks
{
  //! Model unit test interface.
  class TransportLayerMock : public sip0x::TransportLayer {
  protected:
  
    TransportLayerMock(void);
    virtual ~TransportLayerMock(void);
  
    virtual void send(std::shared_ptr<sip0x::Transaction>& transaction, std::shared_ptr<sip0x::protocol::SIPMessage> const& message) override;
    virtual void on_receive(std::shared_ptr<sip0x::protocol::SIPMessage> const& message) override;
  public:
  };
}

#endif // SIP0X_TRANSPORTLAYERMOCK_HPP__
