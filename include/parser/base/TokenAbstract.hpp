#if !defined(SIP0X_PARSER_TOKENABSTRACT_HPP__)
#define SIP0X_PARSER_TOKENABSTRACT_HPP__

#include <string>
#include <algorithm>

#include "parser/base/ReadResult.hpp"
#include "parser/factory/FactoryContext.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"

#include "utils/InputTokenStream.hpp"

namespace Sip0x
{
  namespace Parser
  {
    using namespace Sip0x::Utils::Log;
    class FactoryContext;

    class TokenAbstract {

    protected:
      std::string _name;
      std::shared_ptr<Logger> _logger;

    public:
      TokenAbstract(std::string name, TokenAbstract* root = nullptr) : _name(name) {
      }

      virtual ~TokenAbstract(void) {}


      // Returns a tuple with:
      //  0: result (true or false)
      //  1: parsed string.
      //  1: unique pointer to an allocated object.
      virtual ReadResult read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx = nullptr) const {
        ReadResult output;
        
        if (iss.eof()) {
          DEBUG(_logger, "Stream is empty, skipping...");
          //return output;
        }

        int initial_pos = iss.pos();
        
        DEBUG(_logger, "Saved position %lld during parsing.", (long long)initial_pos);

        FactoryContext* factory = create_factory(ctx);
        output = handle_read(iss, factory != nullptr ? factory : ctx);

        if (output.successes) {
          int delta = iss.pos() - initial_pos;
          std::string parsed = iss.str(initial_pos, delta);
          DEBUG(_logger, "Consumed chars %d during parsing, parsed %s.", delta, parsed.c_str());

          output.parsed = parsed;
        }
        else {
          iss.seekg(initial_pos);
          DEBUG(_logger, "Restored position %lld during parsing.", (long long)initial_pos);

          if (output.errorpos == -2) {
            output.set_error(initial_pos, "Failed parsing token " + std::string(get_name()));
          }
        }

        if (output.successes) {
          if (factory != nullptr) {
            factory->create(this, output);
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


      // Returns a tuple with:
      //  0: result (true or false)
      //  1: unique pointer to an allocated object.
      virtual ReadResult  handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const = 0;

      // Factory event

      virtual FactoryContext* create_factory(FactoryContext* parent) const {
        //return new FactoryContext();
        return nullptr;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENABSTRACT_HPP__
