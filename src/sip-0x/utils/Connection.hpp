#if !defined(SIP0X_LOGIC_CONNECTION_HPP__)
#define SIP0X_LOGIC_CONNECTION_HPP__


#include "asio_header.hpp"

#include <string>
#include <memory>


namespace sip0x
{
  namespace listeners {
    class ConnectionListener;
  }

  namespace utils {

    class ConnectionManager;
    class Logger;
    
    class Connection : public std::enable_shared_from_this<Connection> {
    protected:
      // Infrastructure-
      std::shared_ptr<sip0x::utils::Logger> _logger;
      // Network
      asio::ip::tcp::socket _socket;
      // Buffers
      uint8_t _rbuffer[1024 * 8];
      uint8_t _wbuffer[1024 * 8];

      // Events
      std::shared_ptr<sip0x::listeners::ConnectionListener> _listener;

    public:
      Connection(asio::ip::tcp::socket socket, std::shared_ptr<sip0x::listeners::ConnectionListener> listener);

      virtual ~Connection(void);

      uint32_t get_remote_ip(void);

      uint16_t get_remote_port(void);


      void connect(asio::ip::tcp::resolver::iterator endpoint_iterator);
      void close(void);
      void async_connect(asio::ip::tcp::resolver::iterator endpoint_iterator);
      void async_read(void);
      void async_write(unsigned char* buffer, std::size_t length);
    };
  }
}

#endif // SIP0X_LOGIC_CONNECTION_HPP__
