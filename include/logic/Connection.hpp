#if !defined(SIP0X_LOGIC_CONNECTION_HPP__)
#define SIP0X_LOGIC_CONNECTION_HPP__

#include "asio_header.hpp"

#include <string>
#include <memory>

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"
//#include "utils/Listeners.hpp"


namespace sip0x
{
  namespace Logic
  {
    using namespace sip0x::Utils;
    using namespace sip0x::Utils::Log;
    class ConnectionManager;
    class Connection;

    class ConnectionListener {
    public:
      virtual void on_incoming_data(Connection* conn, uint8_t* buffer, std::size_t size) = 0;
    };

    /// Implement basic logic of a SIP User-Agent.
    class Connection : public std::enable_shared_from_this<Connection> {
    protected:
      // Infrastructure
      Logger* _logger;
      // Network
      asio::ip::tcp::socket _socket;
      ConnectionManager* _manager;
      // Buffers
      uint8_t _rbuffer[1024 * 8];
      uint8_t _wbuffer[1024 * 8];

      // Events
      ConnectionListener* _listener;

    public:
      Connection(asio::ip::tcp::socket socket, ConnectionManager* manager, ConnectionListener* listener) : _socket(std::move(socket)), _manager(manager), _listener(listener) {
      }

      virtual ~Connection(void) {
      }

      uint32_t get_remote_ip(void) {
        // TODO: Write better code for these steps.
        return _socket.remote_endpoint().address().to_v4().to_ulong();
      }

      uint16_t get_remote_port(void) {
        // TODO: Write better code for these steps.
        return _socket.remote_endpoint().port();
      }


      void connect(asio::ip::tcp::resolver::iterator endpoint_iterator) {
        asio::connect(_socket, endpoint_iterator);
      }

      void close(void) {

      }

      void async_connect(asio::ip::tcp::resolver::iterator endpoint_iterator) {
        asio::async_connect(_socket, endpoint_iterator,
        [this](std::error_code ec, asio::ip::tcp::resolver::iterator)
        {
          if (!ec)
          {
            //do_read_header();
          }
        });
      }

      void async_read(void) {
        auto self(shared_from_this());
        _socket.async_read_some(asio::buffer(_rbuffer, sizeof(_rbuffer)),
        [this, self](std::error_code error, std::size_t length) {
          if (!error) {
            _listener->on_incoming_data(this, _rbuffer, length);
          }
        });
      }

      void async_write(unsigned char* buffer, std::size_t length) {
        std::memcpy(_wbuffer, buffer, length);
        auto self(shared_from_this());
        asio::async_write(_socket, asio::buffer(_wbuffer, length),
        [this, self](std::error_code ec, std::size_t /*length*/) {
          if (!ec)
          {
          }
        });
      }
    };
  }
}

#endif // SIP0X_LOGIC_CONNECTION_HPP__
