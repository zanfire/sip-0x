#if !defined(SIP0X_LOGIC_TRANSPORTLAYERTCP_HPP__)
#define SIP0X_LOGIC_TRANSPORTLAYERTCP_HPP__

#include "TransportLayer.hpp"

#include "utils/ConnectionManager.hpp"
#include "utils/asio_header.hpp"
#include "utils/ThreadedObject.hpp"
#include "listeners/ConnectionListener.hpp"

#include <string>
#include <memory>
#include <thread>

namespace sip0x
{
  class TransportLayerTCP : public listeners::ConnectionListener,
                            public sip0x::utils::enable_protected_dtor<TransportLayerTCP>, 
                            public std::enable_shared_from_this<TransportLayerTCP>,
                            public sip0x::utils::ThreadedObject,
                            public sip0x::TransportLayer {

    friend class sip0x::utils::enable_protected_dtor<TransportLayerTCP>;
  protected:
    std::string _bind_address;
    int _bind_port;
    // Network
    asio::io_service _io_service;
    asio::ip::tcp::socket _tcp_socket;
    //asio::ip::udp::socket _udp_socket; 
    asio::ip::tcp::acceptor _acceptor;
    utils::ConnectionManager _connection_manager;

  public:
    //! Process network stuff.
    virtual void process(void) override;

    void async_accept(void);

    virtual void send(std::shared_ptr<Transaction>& transaction, std::shared_ptr<const sip0x::protocol::SIPMessage>& message) override;
    
    virtual void on_incoming_data(std::shared_ptr<utils::Connection> conn, uint8_t const* buffer, std::size_t const size) override;
    
    std::shared_ptr<utils::Connection> connect(std::string const& address, int port);
    uint32_t resolve(std::string const& address);

  protected:
    TransportLayerTCP(std::string const& bind_address, int bind_port);
    virtual ~TransportLayerTCP(void);
  };
}

#endif // SIP0X_LOGIC_TRANSPORTLAYERTCP_HPP__
