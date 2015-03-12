#if !defined(SIP0X_PARSER_READRESULT_HPP__)
#define SIP0X_PARSER_READRESULT_HPP__

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


#include <tuple>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

namespace sip0x
{
  namespace Parser
  {
    using namespace sip0x::Utils;

    //! 
    //! \brief
    //! 
    struct ReadResult {
      bool successes = false;
      uint32_t pos = 0;
      uint32_t len = 0;
      // Error position.
      std::streamoff errorpos = -1;
      std::string* errormessage = nullptr;

      ReadResult(bool s = false, uint32_t pos_ = 0, uint32_t len_ = 0) : successes(s), pos(pos_), len(len_) {
      }
      
      void set_error(std::streamoff pos, std::string message) {
        errorpos = pos;
        if (errormessage != nullptr) delete errormessage;
        errormessage = new std::string(message);
      }
    };
  }
}

#endif // SIP0X_PARSER_READRESULT_HPP__
