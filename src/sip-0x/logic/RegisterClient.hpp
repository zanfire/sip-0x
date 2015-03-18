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

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

#include "logic/UAC.hpp"

#include <chrono>

namespace sip0x
{
  namespace Logic
  {
    using namespace sip0x::utils;

    //!
    //! \brief Keeps a registration to a REGISTRAR server
    //!
    //! Initiate and refresh a registration method toa remote REGISTRAR server.
    //! 
    //!
    //! \todo Design this 
    //!
    class RegisterClient : public UAListener {
    public:
      //! Enumeration of all possible registration status.
      enum RegisterStatus {
        REG_STATUS_NOT_REGISTERED,
        REG_STATUS_REGISTERING,
        REG_STATUS_REGISTERED,
        REG_STATUS_REGISTER_FAILED,
      };

    protected:
      std::shared_ptr<Logger> _logger;
      UAC* _uac;
      // TODO: Needed it is a network stuff?
      std::string _registrar_server;
      int _registrar_port;
      //! Desired REGISTER duration in seconds.
      //! \note Default 7200 seconds.
      uint32_t _desired_expires_secs = 7200;
      //! Registration expires provided by registrar.
      uint32_t _remote_expires_secs;
      std::string _callID; /// \todo needed?
      //! CSeq value.
      uint32_t _cseq; //! it is global for the endpoint or it is unrelated to other sip method?
      //! Registration status.
      RegisterStatus _status = REG_STATUS_NOT_REGISTERED;
      //!
      std::chrono::steady_clock::time_point _last_success_regsitration;
      
      //
      //Transaction _curren_transaction;

    public:
      RegisterClient(UAC* uac, std::string remote_server, int remote_port) : 
        UAListener(),
        _uac(uac), _registrar_server(remote_server), _registrar_port(remote_port)
      {
        _logger = LoggerFactory::get_logger("sip0x.RegisterClient");
        _uac->add_listener(this);
      }

      virtual ~RegisterClient(void) {
        _uac->remove_listener(this);
      }

      //! Set the desired amount of seconds of REGISTER expires. 
      void set_desired_expires(uint32_t e) {
        _desired_expires_secs = e;
      }

      //! Starts the registration process and keep refresh.
      void on_process(void) {
        if (_status == REG_STATUS_NOT_REGISTERED) {
          // RegClient is not registered, so try to register.

          auto request = _uac->create_REGISTER();
          request->uri.hostport.host = _registrar_server;
          request->uri.hostport.port = _registrar_port;

          _uac->handle(request);

          _status = REG_STATUS_REGISTERING;
        }
        else if (_status == REG_STATUS_REGISTERING) {
        }
        else if (_status == REG_STATUS_REGISTERED) {
          // refresh registration if it's time
          auto elapsed_secs = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _last_success_regsitration);

          long long timeout = (long long)std::roundl((float)_remote_expires_secs * 0.85f);
          if (elapsed_secs.count() >= timeout) {
            LOG_INFO(_logger, "Registration near to expiration, expires %lld seconds, elapsed %lld seconds. Initiating registration refresh.", timeout, elapsed_secs.count());

            // TODO: Update registration, don't create a new one.
            auto request = _uac->create_REGISTER();
            request->uri.hostport.host = _registrar_server;
            request->uri.hostport.port = _registrar_port;

            _uac->handle(request);
            _status = REG_STATUS_REGISTERING;
          }
        }
        else if (_status == REG_STATUS_REGISTER_FAILED) {
        }
      }

      std::string describe_status(void) {
        return to_string(_status);
      }


      virtual void on_response(std::shared_ptr<Transaction>& tran, std::shared_ptr<SIPResponse>& response) override {
        // Get expires timeout 
        if (response->is_success()) {
          // The expires could be placed in different places.
          int expires = -1;
          // - Get from contact
          std::shared_ptr<SIPMessageHeaderContact> contact = response->get_first<SIPMessageHeaderContact>();
          if (contact != nullptr) {
            for (auto p : contact->params) {
              if (p.first.compare("expires") == 0) {
                // TODO: Add sanity check or implement sanity check in parsing phase.
                int ex = std::atoi(p.second.c_str());
                LOG_DEBUG(_logger, "Extracted expires timeout of %d seconds from contact header line.", expires);
                break;
              }
            }
          }
          // - Get from header line expires
          if (expires == -1) {
            std::shared_ptr<SIPMessageHeaderExpires> expires_line = response->get_first<SIPMessageHeaderExpires>();
            if (expires_line != nullptr) {
              unsigned long ex = expires_line->expires;
              if (ex >= INT_MAX) {
                LOG_WARN(_logger, "Received a expires timeout of %lu seconds, excised max value from RFC 3261, truncating value to %d seconds.", ex, INT_MAX - 1);
                ex = INT_MAX - 1;
              }
              expires = ex;
              LOG_DEBUG(_logger, "Extracted expires timeout of %d seconds from Expires header line.", expires);
            }
          }

          if (expires > 0) {
            _last_success_regsitration = std::chrono::steady_clock::now();
            _remote_expires_secs = expires;
            _status = REG_STATUS_REGISTERED;
          }
          else {
            _status = REG_STATUS_NOT_REGISTERED;
            LOG_INFO(_logger, "Registration rejected, registrar responded with an invalid or 0 expires timeout.");
          }
        }
        else if (!response->is_provisional()) {
          // TODO: logs
          // TODO: redirect and other steps should be handled in the correct way.
          _status = REG_STATUS_REGISTER_FAILED;
        }
      }

      static char const* to_string(RegisterStatus status) {
        if (status == RegisterStatus::REG_STATUS_NOT_REGISTERED)        return "REG_STATUS_NOT_REGISTERED";
        else if (status == RegisterStatus::REG_STATUS_REGISTERED)       return "REG_STATUS_REGISTERED";
        else if (status == RegisterStatus::REG_STATUS_REGISTERING)      return "REG_STATUS_REGISTERING";
        else if (status == RegisterStatus::REG_STATUS_REGISTER_FAILED)  return "REG_STATUS_REGISTER_FAILED";
        
        return "???";
      }
    };
  }
}

#endif // SIP0X_REGISTERCLIENT_HPP__
