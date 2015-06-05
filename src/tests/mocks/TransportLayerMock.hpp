#if !defined(SIP0X_TRANSPORTLAYERMOCK_HPP__)
#define SIP0X_TRANSPORTLAYERMOCK_HPP__

#include "TransportLayer.hpp"

#include <string>

namespace mocks
{
  //! Model unit test interface.
  class TransportLayerMock : public sip0x::TransportLayer {
  protected:
  
    TransportLayerMock(std::string const& name, std::string const& desc);
    virtual ~TransportLayerMock(void);
  
  public:
  };
}

#endif // SIP0X_TRANSPORTLAYERMOCK_HPP__
