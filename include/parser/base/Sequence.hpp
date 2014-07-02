#if !defined(SIP0X_PARSER_SEQUENCE_HPP__)
#define SIP0X_PARSER_SEQUENCE_HPP__

#include "parser/base/TokenAbstract.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // Generic definition.
    template<typename... Arguments>
    class Sequence;

    // Base definition.
    template<typename First>
    class Sequence<First> : public TokenAbstract{

    protected:
      std::shared_ptr<Logger> _logger;
      First member;

    public:
      Sequence(First f) : TokenAbstract("Sequence"), member(f) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.Sequence");
        _name += "..." + f.get_name();
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
        _name += "," + f.get_name();
      }

      virtual ~Sequence(void) {
      }

    
      First const* first(void) const {
        return &member;
      }

      Sequence<Rest...> const& rest(void) const {
        return *this;
      }

      
      virtual void set_parent(TokenAbstract* parent) override {
        _parent = parent;
        set_parent_variadic(parent, first(), rest());
        // for each 
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        return processing(iss, ctx, first(), rest());
      }

      template<typename F, typename R>
      ReadResult processing(Sip0x::Utils::InputTokenStream& iss, void* ctx, F const* f, R const& r) const {
        
        DEBUG(_logger, "Processing %s ...", f->get_name().c_str());

        ReadResult result = f->read(iss, ctx);
        if (!result.successes) {
          if (result.errorpos == -2) {
            result.set_error(iss.pos(), "Expected token " + f->get_name());
          }
          return result;
        }
        
      
        if ((void*)f != (void*)r.first()) {
          return processing(iss, ctx, r.first(), r.rest());
        }
        else {
          return ReadResult(true);
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_SEQUENCE_HPP__
