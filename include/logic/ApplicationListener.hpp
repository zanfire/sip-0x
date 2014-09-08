#if !defined(SIP0X_LOGIC_APPLICATIONLISTENER_HPP__)
#define SIP0X_LOGIC_APPLICATIONLISTENER_HPP__

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

#include <memory>

#include "protocol/SIP.hpp"

namespace sip0x
{
  namespace Logic
  {
    //! Signaling callback. 
    class SignalingListener {
    public:
      //!
      virtual bool on_receive(std::shared_ptr<SIPRequest> request) = 0;

      //!
      virtual bool on_receive(std::shared_ptr<SIPResponse> response) = 0;
    };

    //! Registration callback
    class RegistrationListener {
    public:
      virtual void on_registered() = 0;
      virtual void on_registration_failed(int error_code) = 0;
    };

    //! Registrar Listener
    class RegistrarListener {
    public:
      virtual void on_registering(std::shared_ptr<SIPResponse> response) = 0;
    };

  }
}

#endif // SIP0X_LOGIC_APPLICATIONLISTENER_HPP__