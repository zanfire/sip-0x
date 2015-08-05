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

#include "UAC.hpp"

#include "listeners/UAListener.hpp"
#include "utils/utils.hpp"

#include <memory>
#include <condition_variable>

namespace sip0x
{
  namespace utils {
    class Logger;
  }
  namespace protocol {
    class SIPResponse;
  }

  //!
  //! \brief Keeps a registration to a REGISTRAR server
  //!
  //! Initiate and refresh a registration method toa remote REGISTRAR server.
  //! 
  //!
  //! \todo Design this 
  //!
  class RegisterClient : public listeners::UAListener, public std::enable_shared_from_this<RegisterClient>, public sip0x::utils::enable_protected_dtor<RegisterClient> {
    friend class sip0x::utils::enable_protected_dtor < RegisterClient > ;

  public:
    //! Enumeration of all possible registration status.
    enum RegisterStatus {
      REG_STATUS_NOT_REGISTERED,
      REG_STATUS_REGISTERING,
      REG_STATUS_REGISTERED,
      REG_STATUS_REGISTER_FAILED,
    };

  protected:
    std::shared_ptr<utils::Logger> _logger;
    std::recursive_mutex _mtx;
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
    //! Last unprocessed response.
    std::shared_ptr<protocol::SIPResponse> _last_unporcessed_response;

  protected:
    RegisterClient(UAC* uac, std::string remote_server, int remote_port);
    virtual ~RegisterClient(void);
  public:

    void start(void);

    //! Set the desired amount of seconds of REGISTER expires. 
    void set_desired_expires(uint32_t e);

    //! Starts the registration process and keep refresh.
    void on_process(void);
    std::string describe_status(void);
    //!
    virtual void on_response(const std::shared_ptr<Transaction>& tran, const std::shared_ptr<protocol::SIPResponse const>& response) override;

    //! Utility method that returns a string for each RegisterStatus.
    static char const* to_string(RegisterStatus status);
  };
}

#endif // SIP0X_REGISTERCLIENT_HPP__
