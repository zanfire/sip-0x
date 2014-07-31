#if !defined(SIP0X_LOGIC_UAC_HPP__)
#define SIP0X_LOGIC_UAC_HPP__

#include "asio_header.hpp"

#include <string>
#include <memory>

#include "parser/Parser.hpp"

#include "logic/UA.hpp"
#include "logic/Connection.hpp"
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
    class UAC : public UA {
    protected:
      // Network
      std::shared_ptr<Connection> _connection;

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

#endif // SIP0X_LOGIC_UAS_HPP__
