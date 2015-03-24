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


namespace sip0x
{
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
    RegisterClient(UAC* uac, std::string remote_server, int remote_port);
    virtual ~RegisterClient(void);

    //! Set the desired amount of seconds of REGISTER expires. 
    void set_desired_expires(uint32_t e);

    //! Starts the registration process and keep refresh.
    void on_process(void);
    std::string describe_status(void);

    //!
    virtual void on_response(std::shared_ptr<Transaction>& tran, std::shared_ptr<SIPResponse>& response) override;

    //! Utility method that returns a string for each RegisterStatus.
    static char const* to_string(RegisterStatus status);
  };
}

#endif // SIP0X_REGISTERCLIENT_HPP__
