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

#include <string>
#include <memory>
#include <set>
#include <condition_variable>
#include <mutex>

#include "ApplicationDelegate.hpp"
#include "utils/ThreadedObject.hpp"

namespace sip0x
{
  namespace utils {
    class Logger;
  }

  class UAC;
  class UAS;
  class TransportLayerTCP;
  class TransactionLayer;
  class RegisterClient;

  //!
  //! Models an endpoint.
  //! 
  //! \remarks This class is thread safe.
  //! \author Matteo Valdina  
  //!
  class Endpoint : public ApplicationDelegate, public utils::ThreadedObject {
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
    std::shared_ptr<utils::Logger> _logger;
    bool _initialized = false;
    UAC* _uac = nullptr;
    UAS* _uas = nullptr;
    std::shared_ptr<TransportLayerTCP> _transport = nullptr;
    TransactionLayer* _transaction = nullptr;
    std::set<std::shared_ptr<RegisterClient>> _register_clients;
    //std::set<Call> _calls;
    //UserService _location_service;
    //RoutingService

    // Threading stuff.
    const int _thread_min_resolution_ms = 20;
    std::recursive_mutex _mtx;
      
  public:
    Endpoint(void);
    virtual ~Endpoint(void);

    //! Initialize Endpoint with the current configuration.
    //!
    //! \arg configuration is new configuration that are applied to endpoint
    //!
    //! \remarks If Endpoint was initialized caller must un-initialize 
    //!   Endpoint before call initialize.
    bool initialize(EndpointConfig const& configuration);

    //! Uninitialize endpoint.
    bool unitialize(void);

    //! Register endpoint to a remote server
    //! \arg remote_server address of the remote server.
    //! \arg remote_port remote port.
    //! \arg refresh_timeout_secs is desired refresh timeout in seconds.
    void register_to(std::string contact, std::string remote_server, int remote_port = 5060, uint32_t refresh_timeout_secs = 3600);
    //!
    //! Getter
    //!

    //! \return Returns Endpoint configuration.
    //EndpointConfig const& configuration(void) const { return _configuration; }

    //! Returns a friendly description of endpoint status.
    std::string describe_status();
  protected:
    virtual void process(void) override;
  };
}

#endif // SIP0X_LOGIC_ENDPOINT_HPP__
