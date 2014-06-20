#if !defined(SIP0X_PARSER_ALTERNATIVE_HPP__)
#define SIP0X_PARSER_ALTERNATIVE_HPP__

#include <string>
#include <memory>
#include <iostream>

#include "parser/base/OpAbstract.hpp"
#include "parser/base/OpOccurrence.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // Generic definition.
    template<typename... Arguments>
    class Alternative;

    // Base definition.
    template<typename First>
    class Alternative<First> : public OpAbstract {

    protected:
      std::shared_ptr<Logger> _logger;
      First member;

    public:
      Alternative(First f) : OpAbstract(), member(f) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.Alternative");
      }

      virtual ~Alternative(void) {}

      First const* first(void) const {
        return &member;
      }
      
      Alternative<First> const& rest(void) const {
        return *this;
      }
    };

    /// Recursion definition...
    template<typename First, typename ... Rest>
    class Alternative<First, Rest...> : public Alternative<Rest...> {
    protected:
      // Reference to the first elemenet of the variadic template.
      First member;
    
    public:
      Alternative(First& f, Rest&... rest) : Alternative<Rest...>(rest...), member(f) {
      }

      virtual ~Alternative(void) {
      }

    
      First const* first(void) const {
        return &member;
      }

      Alternative<Rest...> const& rest(void) const {
        return *this;
      }

    protected:
      virtual ReadResult handle_read(std::istringstream& iss) const override {
        return processing(iss, first(), rest());
      }

      template<typename T>
      ReadResult processing(std::istringstream& iss, First const* f, T const& r) const {
        
        DEBUG(_logger, "Processing %s ...", f->get_name().c_str());

        ReadResult result = f->read(iss);
        if (result.successes) {
          DEBUG(_logger, "Alternative %s successes.", f->get_name().c_str());
          return result;
        }
        
        if (f != r.first()) {
          return processing(iss, r.first(), r.rest());
        }
        else {
          DEBUG(_logger, "No alternative parsed correctly.");
          return ReadResult(false);
        }

      }
    };


    template <typename... Args>
    Alternative<Args...> make_alternative(Args&&... args) {
      return Alternative<Args...>((args)...);
    }
  }
}

#endif // SIP0X_PARSER_ALTERNATIVE_HPP__
