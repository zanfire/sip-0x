#if !defined(SIP0X_LOGIC_UAS_HPP__)
#define SIP0X_LOGIC_UAS_HPP__

#include "asio_header.hpp"

#include <string>
#include <memory>

#include "parser/Parser.hpp"

#include "logic/UA.hpp"
#include "logic/ConnectionManager.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"
#include "utils/InputTokenStream.hpp"

namespace Sip0x
{
  namespace Logic
  {
    using namespace Sip0x::Utils::Log;

    /// Implement basic logic of a SIP User-Agent.
    class UAS : public UA {
    protected:
      // Network
      asio::ip::tcp::socket _socket;
      asio::ip::tcp::acceptor _acceptor;
      ConnectionManager _connection_manager;

    public:
      UAS(std::string useragent, asio::io_service& io_service, int port) : UA(io_service, useragent),
        _socket(io_service),
        _acceptor(io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
        _logger = LoggerManager::get_logger("Sip0x.Logic.UAS");
      }

      virtual ~UAS(void) {
      }

      void process(void) {
        // Install async operation.
        async_accept();
        // process async operation.
        _io_service.run();
      }
    
      void async_accept(void) {
        _acceptor.async_accept(_socket, [this](std::error_code ec) {
          if (!ec) {
            _connection_manager.add(std::make_shared<Connection>(std::move(_socket), &_connection_manager, this));
          }
          async_accept();
        });
      }

    private:
      virtual void onIncomingData(uint8_t* buffer, std::size_t size) override {
        InputTokenStream iss(buffer, size);
        Sip0x::Protocol::SIPMessage* message = Sip0x::Parser::parse_sip_message(iss);
        if (message != nullptr) {
          message->write(std::cout);
        }
      }
    };
  }
}

#endif // SIP0X_LOGIC_UAS_HPP__
