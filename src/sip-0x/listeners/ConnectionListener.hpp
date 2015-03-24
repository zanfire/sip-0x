#if !defined(SIP0X_LOGIC_UALISTENER_HPP__)
#define SIP0X_LOGIC_UALISTENER_HPP__

#include <memory>

namespace sip0x
{
  class ConnectionListener {
  public:
    virtual void on_incoming_data(Connection* conn, uint8_t* buffer, std::size_t size) = 0;
  };

}

#endif // SIP0X_LOGIC_UALISTENER_HPP__
