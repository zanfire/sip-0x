#if !defined(SIP0X_REGISTRAR_HPP__)
#define SIP0X_REGISTRAR_HPP__

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
    using namespace sip0x::Utils;

    //!
    //! \brief Registrar 
    //!
    //! This class implement a registrar. A registrar keeps track of registered client
    //!
    //! \todo Design this 
    //!
    class Registrar : public UAListener {
    protected:
      std::shared_ptr<Logger> _logger;

    public:
      Registrar(UAC* uac, std::string remote_server, int remote_port) : 
        UAListener()
      {
        _logger = LoggerFactory::get_logger("sip0x.Registrar");
      }

      virtual ~Registrar(void) {
      }

    };
  }
}

#endif // SIP0X_REGISTRAR_HPP__
