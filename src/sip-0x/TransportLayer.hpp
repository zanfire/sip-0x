#if !defined(SIP0X_LOGIC_TRANSPORTLAYER_HPP__)
#define SIP0X_LOGIC_TRANSPORTLAYER_HPP__

#include <string>
#include <memory>
#include <thread>

#include "utils/ConnectionManager.hpp"
#include "utils/asio_header.hpp"

#include "listeners/ConnectionListener.hpp"

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


  class TransportLayer : public listeners::ConnectionListener, std::enable_shared_from_this<TransportLayer> {
  protected:
    // Infrastructure
    std::shared_ptr<utils::Logger> _logger;
    std::shared_ptr<utils::Logger> _logger_siptrace;
    std::string _bind_address;
    int _bind_port;
    bool _thread_must_stop = false;
    // Threading
    std::thread* _thread = nullptr;
    // Network
    asio::io_service _io_service;
    asio::ip::tcp::socket _tcp_socket;
    //asio::ip::udp::socket _udp_socket; 
    asio::ip::tcp::acceptor _acceptor;
    utils::ConnectionManager _connection_manager;
    // Callbakcs
    listeners::TransportListener* _listener = nullptr;

  public:
    //! \todo Use bind address
    TransportLayer(std::string const& bind_address, int const& bind_port);
    virtual ~TransportLayer(void);

    //void set_listener(TransportListener* l)  { _listener  = l; }

    //! Start transport layer. 
    //! \returns true if transport layer was in
    void start(void);

    //! Stop transport layer.
    //! \remark Returns in a synchronous way.
    void stop(void);
    void send(std::shared_ptr<Transaction>& trnasaction, std::shared_ptr<sip0x::protocol::SIPMessage> const& message);
    //! Process network stuff.
    void process(void);
    void async_accept(void);
    virtual void on_incoming_data(std::shared_ptr<utils::Connection> conn, uint8_t const* buffer, std::size_t const size) override;
    std::shared_ptr<utils::Connection> connect(std::string address, int port);
    uint32_t resolve(std::string address);
  };
}

#endif // SIP0X_LOGIC_UA_HPP__
