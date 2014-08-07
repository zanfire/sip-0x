#if !defined(SIP0X_LOGIC_UA_HPP__)
#define SIP0X_LOGIC_UA_HPP__

#include "asio_header.hpp"

#include <string>
#include <memory>


#include "logic/Connection.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"

namespace Sip0x
{
  namespace Logic
  {
    using namespace Sip0x::Utils::Log;

    /// Implement basic logic of a SIP User-Agent.
    class UA : public ConnectionListener  {
    protected:
      // Infrastructure
      std::shared_ptr<Logger> _logger;
      // Network
      asio::io_service& _io_service;
      asio::ip::tcp::socket _tcp_socket;
      // SIP
      std::string _useragent;

    public:
      UA(asio::io_service& io_service, std::string useragent) : _io_service(io_service), _tcp_socket(io_service), _useragent(useragent) {
      }

      virtual ~UA(void) {
      }

      virtual void onIncomingData(uint8_t* buffer, std::size_t size) override {
        InputTokenStream iss(buffer, size);
        Sip0x::SIPMessage* message = Sip0x::Parser::parse_sip_message(iss);
        if (message != nullptr) {
          message->write(std::cout);
        }
      }
    };

    class UAC : public UA {
    protected:
      // Network
      std::shared_ptr<Connection> _connection;
      // SIP stuff
      std::string _callID;
      std::string _contact;

    public:
      UAC(asio::io_service& io_service, std::string useragent) : UA(io_service, useragent) {
        _logger = LoggerManager::get_logger("Sip0x.Logic.UAC");
        _connection = std::make_shared<Connection>(std::move(_tcp_socket), nullptr, this);
      }

      virtual ~UAC(void) {
      }

      void connect(asio::ip::tcp::resolver::iterator endpoint_iterator) {
        _connection->connect(endpoint_iterator);
      }

      void process(void) {
        _io_service.run();
      }

    };

  }
}

#endif // SIP0X_LOGIC_UA_HPP__
