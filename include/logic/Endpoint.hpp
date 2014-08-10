#if !defined(SIP0X_LOGIC_ENDPOINT_HPP__)
#define SIP0X_LOGIC_ENDPOINT_HPP__

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

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"

#include "logic/RegisterClient.hpp"
#include "logic/UAC.hpp"
#include "logic/UAS.hpp"
#include "logic/TransportLayer.hpp"
#include "logic/TransactionLayer.hpp"

#include "asio_header.hpp" // TODO: Remove hpp and repalce h.
#include <set>

namespace Sip0x
{
  namespace Logic
  {
    using namespace Sip0x::Utils::Log;

    //!
    //! \brief Models an endpoint.
    //! 
    //! TODO.................
    //! 
    //! \author Matteo Valdina  
    //!
    class Endpoint {

    public:
      //! \brief Endpoint configuration.
      struct EndpointConfig {
        // Network stuff.
        std::string bind_address;
        int bind_port;
        // SIP stuff.
        std::string username;
        std::string domainname;
      };

    protected:
      std::shared_ptr<Logger> _logger;
      bool _initialized = false;
      asio::io_service _io_service;
      UAC _uac;
      //UAS _uas;
      TransportLayer* _transport = nullptr;
      std::set<RegisterClient*> _register_clients;
      //std::set<Call> _calls;
      //UserService _location_service;
      //RoutingService
      
    public:
      Endpoint(void) {
        _logger = LoggerManager::get_logger("sip0x.Endpoint");
      }

      virtual ~Endpoint(void) {
      }

      //! Initialize Endpoint with the current configuration.
      //!
      //! \arg configuration is new configuration that are applyed to endpoint
      //!
      //! \remarks If Endpoint was initialized caller must un-initialize 
      //!   Endpoint before call initialize.
      bool initialize(EndpointConfig const& configuration) {
        if (_initialized) {
          LOG_WARN(_logger, "Skipping initialization because Endpoint was initialized.");
          return false;
        }
        // Initialize transport layer.
        _transport = new TransportLayer(configuration.bind_address, configuration.bind_port);
        _transport->start();

        //_uac = new UAC()
        // Setup TCP
        //
        //
        //Sip0x::Logic::UAC uac(io_service, "sip0x-uac");
        //
        //uac.connect(endpoint_iterator);
        //
        //t.join();



        // Assign to subcomponents the configuration.
        //_uac.
        //_configuration = configuration;

        //

        _initialized = true;
        return true;
      }

      //! Uninitialize endpoint.
      bool unitialize(void) {
        // TODO: Unregister RegisterClients.

        _initialized = false;
        return true;
      }

      //! Register endpoint to a remote server
      //! \arg remote_server address of the remote server.
      //! \arg remote_port remote port.
      //! \arg refresh_timeout_secs is desired refresh timeout in seconds.
      void register_to(std::string contact, std::string remote_server, int remote_port = 5060, uint32_t refresh_timeout_secs = 3600) {
        // TODO: Check if a registration was established.
        
        // Create a register client and start processing.
        RegisterClient* reg = new RegisterClient(&_uac, remote_server, remote_port);
        _register_clients.insert(reg);

        reg->set_desired_expires(refresh_timeout_secs);
        reg->start();
      }

      //!
      //! Getter
      //!

      //! \return Returns Endpoint configuration.
      //EndpointConfig const& configuration(void) const { return _configuration; }

      //! Returns a friendly description of endpoint status.
      std::string describe_status() {
        std::string out;
        out += "Initialized: ";
        if (_initialized) {
          out += "true";
        }
        else {
          out += "false";
        }
        for (auto r : _register_clients) {
          out += ", register client: " + r->describe_status();
        }
        return out;
      }
    };
  }
}

#endif // SIP0X_LOGIC_ENDPOINT_HPP__
