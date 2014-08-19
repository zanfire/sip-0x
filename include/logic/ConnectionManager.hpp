#if !defined(SIP0X_LOGIC_CONNECTIONMANAGER_HPP__)
#define SIP0X_LOGIC_CONNECTIONMANAGER_HPP__

#include "asio_header.hpp"

#include <string>
#include <memory>
#include <set>

#include "logic/Connection.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"
//#include "utils/Listeners.hpp"

namespace sip0x
{
  namespace Logic
  {
    using namespace sip0x::Utils;
    using namespace sip0x::Utils::Log;

    class ConnectionManager {
    protected:
      // Infrastructure
      Logger* _logger;
      // Network
      
      /// The managed connections.
      std::set<std::shared_ptr<Connection>> _connections;

    public:
      ConnectionManager(void) {
      }

      virtual ~ConnectionManager(void) {
      }

      void add(std::shared_ptr<Connection>& connection) {
        _connections.insert(connection);
        // Start reading from connection.
        connection->async_read();
        //connection->open();
      }

      void remove(std::shared_ptr<Connection>& connection) {
        _connections.erase(connection);
        connection->close();
      }
    };
  }
}

#endif // SIP0X_LOGIC_CONNECTIONMANAGER_HPP__
