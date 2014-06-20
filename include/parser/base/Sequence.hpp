#if !defined(SIP0X_PARSER_SEQUENCE_HPP__)
#define SIP0X_PARSER_SEQUENCE_HPP__

#include "parser/base/OpAbstract.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // Generic definition.
    template<typename... Arguments>
    class Sequence;

    // Base definition.
    template<typename First>
    class Sequence<First> : public OpAbstract {

    protected:
      std::shared_ptr<Logger> _logger;
      First member;

    public:
      Sequence(First f) : OpAbstract(), member(f) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.Sequence");
      }

      virtual ~Sequence(void) {}

      First const* first(void) const {
        return &member;
      }
      
      Sequence<First> const& rest(void) const {
        return *this;
      }
    };

    /// Recursion definition...
    template<typename First, typename ... Rest>
    class Sequence<First, Rest...> : public Sequence<Rest...> {
    protected:
      // Reference to the first elemenet of the variadic template.
      First member;
    
    public:
      Sequence(First& f, Rest&... rest) : Sequence<Rest...>(rest...), member(f) {
      }

      virtual ~Sequence(void) {
      }

    
      First const* first(void) const {
        return &member;
      }

      Sequence<Rest...> const& rest(void) const {
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
          DEBUG(_logger, "Sequence %s successes.", f->get_name().c_str());
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
  }
}

#endif // SIP0X_PARSER_SEQUENCE_HPP__
