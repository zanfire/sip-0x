#if !defined(SIP0X_LOGIC_UAC_HPP__)
#define SIP0X_LOGIC_UAC_HPP__

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

#include "asio_header.hpp"

#include <string>
#include <memory>

#include "parser/Parser.hpp"

#include "logic/UA.hpp"
#include "logic/Connection.hpp"
#include "logic/ConnectionManager.hpp"

#include "logic/Transaction.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"
#include "utils/InputTokenStream.hpp"



namespace Sip0x
{
  namespace Logic
  {
    using namespace Sip0x::Utils::Log;

    //!
    //! \brief Models a SIP UAC (User Agent Client). 
    //! 
    //! A UAC is an user-agent that initiate the .... 
    //! TODO.................
    //! 
    //! \author Matteo Valdina  
    //!
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

#endif // SIP0X_LOGIC_UAS_HPP__
