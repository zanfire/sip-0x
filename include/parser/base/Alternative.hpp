#if !defined(SIP0X_PARSER_ALTERNATIVE_HPP__)
#define SIP0X_PARSER_ALTERNATIVE_HPP__

#include "parser/base/TokenAbstract.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // Generic definition.
    template<typename... Arguments>
    class Alternative;

    // Base definition.
    template<typename First>
    class Alternative<First> : public TokenAbstract {

    protected:
      std::shared_ptr<Logger> _logger;
      First member;

    public:
      Alternative(First& f) : TokenAbstract("Alternative"), member(f) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.Alternative");
        _name += "..." + f.get_name();
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
      // Reference to the first element of the variadic template.
      First member;
    
    public:
      Alternative(First& f, Rest&... rest) : Alternative<Rest...>(rest...), member(f) {
        _name += "," + f.get_name();
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
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        return processing(iss, ctx, first(), rest());
      }

      template<typename F, typename R>
      ReadResult processing(Sip0x::Utils::InputTokenStream& iss, void* ctx, F const* f, R const& r) const {
        
        DEBUG(_logger, "Processing %s ...", f->get_name().c_str());

        ReadResult result = f->read(iss, ctx);
        if (result.successes) {
          DEBUG(_logger, "Alternative %s successes.", f->get_name().c_str());
          return result;
        }
        
        if ((void*)f != (void*)r.first()) {
          return processing(iss, ctx, r.first(), r.rest());
        }
        else {
          DEBUG(_logger, "No alternative parsed correctly.");
          return ReadResult(false);
        }

      }
    };
  }
}

#endif // SIP0X_PARSER_ALTERNATIVE_HPP__
