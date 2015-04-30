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

#include <string>
#include <mutex>
#include <memory>
#include <set>

namespace sip0x
{
  namespace utils {
    class Logger;
    class Connection;

    //! Connections manager.
    //!
    //! This class handle multiple connections and provide a centralized access 
    //! each connection.
    class ConnectionManager {
    protected:
      std::shared_ptr<Logger> _logger;
      std::recursive_mutex _mtx;

      /// The managed connections.
      std::set<std::shared_ptr<Connection>> _connections;

    public:
      ConnectionManager(void);
      virtual ~ConnectionManager(void);

      //! Add given connection to manager.
      void add(std::shared_ptr<Connection>& connection);
      //! Remove given connection from manager.
      void remove(std::shared_ptr<Connection>& connection);

      //! Search connection by IPv4 and port.
      std::shared_ptr<Connection> get(uint32_t remote_ip, uint16_t remote_port);
    };
  }
}

#endif // SIP0X_LOGIC_CONNECTIONMANAGER_HPP__
