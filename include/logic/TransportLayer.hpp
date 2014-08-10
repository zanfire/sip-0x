#if !defined(SIP0X_LOGIC_TRANSPORTLAYER_HPP__)
#define SIP0X_LOGIC_TRANSPORTLAYER_HPP__

#include "asio_header.hpp"

#include <string>
#include <memory>
#include <thread>

#include "logic/Connection.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"

namespace Sip0x
{
  namespace Logic
  {
    using namespace Sip0x::Utils::Log;

    class TransportLayer : public ConnectionListener  {
    protected:
      // Infrastructure
      std::shared_ptr<Logger> _logger;
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
      ConnectionManager _connection_manager;

    public:
      //! \todo Use bind address
      TransportLayer(std::string const& bind_address, int const& bind_port) :
        ConnectionListener(),
        _bind_address(bind_address),
        _bind_port(bind_port),
        _thread(),
        _io_service(),
        _tcp_socket(_io_service), 
        _acceptor(_io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), bind_port)) {

        //asio::ip::tcp::resolver resolver(_io_service);
        //auto endpoint_iterator = resolver.resolve( { _bind_address, std::to_string(_bind_port) } );
      }

      virtual ~TransportLayer(void) {
      }

      virtual void onIncomingData(uint8_t* buffer, std::size_t size) override {
        InputTokenStream iss(buffer, size);
        Sip0x::SIPMessage* message = Sip0x::Parser::parse_sip_message(iss);
        if (message != nullptr) {
          message->write(std::cout);
        }
      }
    
      void connect(std::string address, int port) {
        asio::ip::tcp::resolver resolver(_io_service);
        auto endpoint_iterator = resolver.resolve({address, std::to_string(port) });

        std::shared_ptr<Connection> connection = std::make_shared<Connection>(std::move(_tcp_socket), nullptr, this);
        connection->connect(endpoint_iterator);
        _connection_manager.add(connection);
      }


      void start(void) {
        //TODO: don't start and foget this thread!!!
        _thread = new std::thread([this](){ process(); });
      }

      
      void process(void) {
        // TODO: logging
        std::cout << "Process thread started.\n";
        while (!_thread_must_stop) {
          // Install async operation.
          async_accept();
          // process async operation.
          _io_service.run();
        }
        std::cout << "Process thread ended.\n";
      }

      void async_accept(void) {
        _acceptor.async_accept(_tcp_socket, [this](std::error_code ec) {
          if (!ec) {
            _connection_manager.add(std::make_shared<Connection>(std::move(_tcp_socket), &_connection_manager, this));
          }
          async_accept();
        });
      }
    };
  }
}

#endif // SIP0X_LOGIC_UA_HPP__
