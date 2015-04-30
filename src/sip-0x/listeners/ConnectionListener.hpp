#if !defined(SIP0X_CONNECTIONLISTENER_HPP__)
#define SIP0X_CONNECTIONLISTENER_HPP__

#include <memory>

namespace sip0x
{
  namespace utils {
    class Connection;
  }

  namespace listeners {
    class ConnectionListener {
    public:
      virtual void on_incoming_data(std::shared_ptr<utils::Connection> conn, uint8_t const* buffer, std::size_t const size) = 0;
    };
  }
}

#endif // SIP0X_CONNECTIONLISTENER_HPP__
