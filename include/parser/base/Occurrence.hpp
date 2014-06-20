#if !defined(SIP0X_PARSER_OCCURRENCE_HPP__)
#define SIP0X_PARSER_OCCURRENCE_HPP__

#include "parser/base/OpAbstract.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // Generic definition.
    template<typename... Arguments>
    class Occurrence;

    // Base definition.
    template<typename First>
    class Occurrence<First> : public OpAbstract {

    protected:
      std::shared_ptr<Logger> _logger;
      First member;

    public:
      Occurrence(First f) : OpAbstract(), member(f) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.Occurrence");
      }

      virtual ~Occurrence(void) {}

      First const* first(void) const {
        return &member;
      }
      
      Occurrence<First> const& rest(void) const {
        return *this;
      }
    };

    /// Recursion definition...
    template<typename First, typename ... Rest>
    class Occurrence<First, Rest...> : public Occurrence<Rest...> {
    protected:
      // Reference to the first elemenet of the variadic template.
      First member;
    
    public:
      Occurrence(First& f, Rest&... rest) : Occurrence<Rest...>(rest...), member(f) {
      }

      virtual ~Occurrence(void) {
      }

    
      First const* first(void) const {
        return &member;
      }

      Occurrence<Rest...> const& rest(void) const {
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
          DEBUG(_logger, "Occurrence %s successes.", f->get_name().c_str());
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

#endif // SIP0X_PARSER_OCCURRENCE_HPP__
