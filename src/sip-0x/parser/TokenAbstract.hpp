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


//#define ENABLE_PARSER_LOGGING

#include <string>
#include <memory>

#include "parser/base/ReadResult.hpp"
#include "parser/factory/FactoryContext.hpp"

#if defined(ENABLE_PARSER_LOGGING)
  #include "utils/LoggerFactory.hpp"
  #include "utils/Logger.hpp"
#endif

#include "utils/InputTokenStream.hpp"

namespace sip0x
{
  namespace Parser
  {
    using namespace sip0x::Utils;
    class FactoryContext;

    class TokenAbstract {

    protected:
      std::string _name;
#if defined(ENABLE_PARSER_LOGGING)
      std::shared_ptr<Logger> _logger;
#endif

    public:
      TokenAbstract(std::string name, TokenAbstract* root = nullptr) : _name(name) {
      }

      virtual ~TokenAbstract(void) {}


      // Returns a tuple with:
      //  0: result (true or false)
      //  1: parsed string.
      //  1: unique pointer to an allocated object.
      virtual ReadResult read(sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx = nullptr) const {
        int initial_pos = iss.pos();
#if defined(ENABLE_PARSER_LOGGING)
        LOG_DEBUG(_logger, "Saved position %lld during parsing.", (long long)initial_pos);
#endif

        FactoryContext* factory = create_factory();
        ReadResult output = handle_read(iss, factory != nullptr ? factory : ctx);

        if (output.successes) {
          //LOG_DEBUG(_logger, "Consumed chars %d during parsing, parsed %s.", delta, parsed.c_str());
        }
        else {
          iss.seekg(initial_pos);
#if defined(ENABLE_PARSER_LOGGING)
          LOG_DEBUG(_logger, "Restored position %lld during parsing.", (long long)initial_pos);
#endif
          if (output.errorpos == -2) {
            output.set_error(initial_pos, "Failed parsing token " + std::string(get_name()));
          }
        }

        if (output.successes) {
          if (factory != nullptr) {
            factory->create(iss.str(initial_pos, iss.pos() - initial_pos));
            ctx->add_child(factory);
          }
        }
        else {
          if (factory != nullptr) {
            delete factory;
          }
        }
        return output;
      }

      void set_name(std::string const& name) { _name = name; }
      std::string const& get_name(void) const { return _name; }

      virtual ReadResult  handle_read(sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const = 0;

      virtual FactoryContext* create_factory(void) const {
        return nullptr;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENABSTRACT_HPP__
