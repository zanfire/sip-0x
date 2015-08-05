#if !defined(SIP0X_LOGIC_CONNECTION_HPP__)
#define SIP0X_LOGIC_CONNECTION_HPP__


#include "asio_header.hpp"

#include <string>
#include <memory>

#include <utils/utils.hpp>

namespace sip0x
{
  namespace listeners {
    class ConnectionListener;
  }

  namespace utils {

    class ConnectionManager;
    class Logger;
    
    class Connection : public std::enable_shared_from_this<Connection>, public sip0x::utils::enable_protected_dtor<Connection> {
      friend class sip0x::utils::enable_protected_dtor<Connection>;
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
      uint32_t get_remote_ip(void);
      uint16_t get_remote_port(void);

      void connect(asio::ip::tcp::resolver::iterator endpoint_iterator);
      void close(void);
      
      void async_read(void);
      void async_write(unsigned char* buffer, std::size_t length);

    protected:
      Connection(asio::ip::tcp::socket& socket, const std::shared_ptr<sip0x::listeners::ConnectionListener>& listener);
      virtual ~Connection(void);

      void async_connect(asio::ip::tcp::resolver::iterator endpoint_iterator);
      
      //! Hanlde the result of read/write operation.
      void handle_read(std::error_code ec, std::size_t length);
      void handle_write(std::error_code ec, std::size_t length);
    };
  }
}

#endif // SIP0X_LOGIC_CONNECTION_HPP__
