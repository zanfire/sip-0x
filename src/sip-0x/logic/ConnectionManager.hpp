#if !defined(SIP0X_LOGIC_CONNECTIONMANAGER_HPP__)
#define SIP0X_LOGIC_CONNECTIONMANAGER_HPP__

//!
//! Copyright 2014 Matteo Valdina
//!
//! Licensed under the Apache License, Version 2.0 (the "License");
//! you may not use this file except in compliance with the License.
//! You may obtain a copy of the License at
//!
//!     http://www.apache.org/licenses/LICENSE-2.0
//!
//! Unless required by applicable law or agreed to in writing, software
//! distributed under the License is distributed on an "AS IS" BASIS,
//! WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//! See the License for the specific language governing permissions and
//! limitations under the License.
//!

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

#include "logic/Connection.hpp"

#include <string>
#include <mutex>
#include <memory>
#include <set>


namespace sip0x
{
  namespace Logic
  {
    using namespace sip0x::Utils;
    using namespace sip0x::Utils;

    class ConnectionManager {
    protected:
      std::shared_ptr<Logger> _logger;
      std::recursive_mutex _mtx;
      
      /// The managed connections.
      std::set<std::shared_ptr<Connection>> _connections;

    public:
      ConnectionManager(void) {
        _logger = LoggerFactory::get_instance()->get_logger("sip0x.ConnectionManager");
      }

      virtual ~ConnectionManager(void) {
      }

      void add(std::shared_ptr<Connection>& connection) {
        _mtx.lock();
        _connections.insert(connection);
        _mtx.unlock();
        // Start reading from connection.
        connection->async_read();
        //connection->open();
      }

      void remove(std::shared_ptr<Connection>& connection) {
        _mtx.lock();
        _connections.erase(connection);
        _mtx.unlock();
        connection->close();
      }


      std::shared_ptr<Connection> get(uint32_t remote_ip, uint16_t remote_port) {
        _mtx.lock();
        std::shared_ptr<Connection> connection;
        for (auto conn : _connections) {
          if (conn->get_remote_ip() == remote_ip && conn->get_remote_port() == remote_port) {
            connection = conn;
            break;
          }
        }
        _mtx.lock();
        void* c = connection.get();
        LOG_DEBUG(_logger, "Searching a connection %hhu.%hhu.%hhu.%hhu:%hu, result %p.", remote_ip, remote_ip >> 8, remote_ip >> 16 , remote_ip >> 24, remote_port, connection.get());
        return connection;
      }
    };
  }
}

#endif // SIP0X_LOGIC_CONNECTIONMANAGER_HPP__
