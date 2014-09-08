#if !defined(SIP0X_LOGIC_APPLICATIONDELEGATE_HPP__)
#define SIP0X_LOGIC_APPLICATIONDELEGATE_HPP__

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

#include <functional>
#include <memory>

#include "protocol/SIP.hpp"

namespace sip0x
{
  namespace Logic
  {
    // Signaling typedefs.
    typedef std::function<bool(std::shared_ptr<SIPMessage>&)> SignalingHandler;
    // Registration
    typedef std::function<void(int const& status, int const& details)> RegisterUpdateHandler;
    // Registrar
    typedef std::function<bool(std::shared_ptr<SIPRequest>&)> RegistrarUpdateHandler;

    class ApplicationDelegate {
    protected:
      SignalingHandler _signaling = nullptr;
      RegisterUpdateHandler _registration_update = nullptr;
      RegistrarUpdateHandler _registrar_update = nullptr;

    public:
      // TODO: Add mtx
      // Signaling typedefs.
      void set_cb_signaling(SignalingHandler handler) { _signaling = handler; }

      bool raise_cb_signaling(std::shared_ptr<SIPMessage>& message) {
        if (_signaling != nullptr) return _signaling(message);
        else return false;
      }

      // Registration
      typedef std::function<void(int const& status, int const& details)> RegisterUpdateHandler;
      void set_cb_registration_update(RegisterUpdateHandler handler) { _registration_update = handler; }
      // Registrar
      void set_cb_registrar_update(RegistrarUpdateHandler handler) { _registrar_update = handler; }

      bool raise_cb_registrar_update(std::shared_ptr<SIPRequest>& request) {
        if (_registrar_update != nullptr) return _registrar_update(request);
        else return false;
      }
    };
  }
}

#endif // SIP0X_LOGIC_APPLICATIONDELEGATE_HPP__