#if !defined(SIP0X_LOGIC_UA_HPP__)
#define SIP0X_LOGIC_UA_HPP__

#include "asio_header.hpp"

#include <string>
#include <memory>


#include "logic/Connection.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"

namespace sip0x
{
  namespace Logic
  {
    using namespace sip0x::Utils::Log;

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

    };
  }
}

#endif // SIP0X_LOGIC_UA_HPP__
