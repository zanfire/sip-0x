#if !defined(SIP0X_LOGIC_CONNECTION_HPP__)
#define SIP0X_LOGIC_CONNECTION_HPP__


#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

#include "asio_header.hpp"

#include <string>
#include <memory>

//#include "utils/Listeners.hpp"


namespace sip0x
{
  using namespace sip0x::utils;
    
  class ConnectionManager;
  class Connection;

  class ConnectionListener {
  public:
    virtual void on_incoming_data(Connection* conn, uint8_t* buffer, std::size_t size) = 0;
  };

  class Connection : public std::enable_shared_from_this<Connection> {
  protected:
    // Infrastructure-
    std::shared_ptr<sip0x::utils::Logger> _logger;
    // Network
    asio::ip::tcp::socket _socket;
    ConnectionManager* _manager;
    // Buffers
    uint8_t _rbuffer[1024 * 8];
    uint8_t _wbuffer[1024 * 8];

    // Events
    ConnectionListener* _listener;

  public:
    Connection(asio::ip::tcp::socket socket, ConnectionManager* manager, ConnectionListener* listener);

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

#endif // SIP0X_LOGIC_CONNECTION_HPP__
