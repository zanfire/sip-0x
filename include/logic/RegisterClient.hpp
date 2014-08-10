#if !defined(SIP0X_REGISTERCLIENT_HPP__)
#define SIP0X_REGISTERCLIENT_HPP__

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

#include "logic/UAC.hpp"


namespace Sip0x
{
  namespace Logic
  {
    using namespace Sip0x::Utils::Log;

    //!
    //! \brief Keeps a registration to a REGISTRAR server
    //!
    //! Initiate and refresh a registration method toa remote REGISTRAR server.
    //! 
    //!
    //! \todo Design this 
    //!
    class RegisterClient {
    public:
      //! Enumeration of all possible registration status.
      enum RegisterStatus {
        REG_STATUS_NOT_REGISTERED,
        REG_STATUS_REGISTERING,
        REG_STATUS_REGISTERED
      };

    protected:
      std::shared_ptr<Logger> _logger;
      UAC* _uac;
      // TODO: Needed it is a network stuff?
      std::string _registrar_server;
      int _registrar_port;
      //! Desired REGISTER duration in seconds.
      //! \note Default 7200 seconds.
      uint32_t _desired_expires = 7200;
      //! It is the remote REGISTRER duration seconds.
      //! The REGISTER method expires after this amounth of seconds
      uint32_t _remote_expires_secs;
      std::string _callID; /// \todo needed?
      //! CSeq value.
      uint32_t _cseq; //! it is global for the endpoint or it is unrelated to other sip method?
      
      RegisterStatus _status = REG_STATUS_NOT_REGISTERED;
      
      //
      //Transaction _curren_transaction;

    public:
      RegisterClient(UAC* uac, std::string remote_server, int remote_port) : 
        _uac(uac), _registrar_server(remote_server), _registrar_port(remote_port)
      {
        _logger = LoggerManager::get_logger("Sip0x.Logic.RegisterClient");
      }

      virtual ~RegisterClient(void) {
      }

      //! Set the desired amount of seconds of REGISTER expires. 
      void set_desired_expires(uint32_t e) {
        _desired_expires = e;
      }

      //! Starts the registration process and keep refresh.
      void start(void) {
        auto request = _uac->create_REGISTER();
        // process 
      }

      std::string describe_status(void) {
        return "uniniplemented!!!";
      }

    protected:

      bool send_REGISTER(void) {
        std::unique_ptr<SIPRequest> req = _uac->create_REGISTER();
        _uac->process(req.get());
      }

      //std::unique_ptr<SIPRequest> create_REGISTER(void) {
      //  std::unique_ptr<SIPRequest> req = _uac->create_REQUEST();
      //}
    };
  }
}

#endif // SIP0X_REGISTERCLIENT_HPP__
