#if !defined(SIP0X_PARSER_TOKENABSTRACT_HPP__)
#define SIP0X_PARSER_TOKENABSTRACT_HPP__

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

#include "utils/InputTokenStream.hpp"

#include "parser/ParserResult.hpp"

namespace sip0x
{
  namespace parser
  {
    class FactoryContext;
    class InputTokenStream;
    class sip0x::utils::Logger;
    
    //! Abstract class of a Token.
    //!
    //! A token is the minimum entity that parser can handle.
    class TokenAbstract {

    protected:
      std::string _name;
      std::shared_ptr<sip0x::utils::Logger> _logger;

    public:
      TokenAbstract(std::string name, TokenAbstract* root = nullptr);
      virtual ~TokenAbstract(void);

      void set_name(std::string const& name) { _name = name; }
      std::string const& get_name(void) const { return _name; }

      // Interface.

      virtual ParserResult read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx = nullptr) const;
      virtual ParserResult  handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const = 0;
      virtual FactoryContext* create_factory(void) const;
    };
  }
}

#endif // SIP0X_PARSER_TOKENABSTRACT_HPP__
