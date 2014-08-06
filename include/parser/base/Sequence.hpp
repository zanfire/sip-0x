#if !defined(SIP0X_PARSER_SEQUENCE_HPP__)
#define SIP0X_PARSER_SEQUENCE_HPP__

#include "parser/base/TokenAbstract.hpp"

namespace Sip0x
{
  namespace Parser
  {
    /// 

    // Generic definition.
    template<typename... Arguments>
    class Sequence;

    // Base definition.
    template<typename First>
    class Sequence<First> : public TokenAbstract {

    protected:
      std::shared_ptr<Logger> _logger;
      First member;
      bool _disable_factory;

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

      void disable_factory(bool disable) {
        _disable_factory = disable;
      }

      virtual FactoryContext* create_factory(void) const override {
        if (_disable_factory) {
          return nullptr;
        }
        else {
          return new FactoryContext();
        }
      }
    };

    /// Recursion definition...
    template<typename First, typename ... Rest>
    class Sequence<First, Rest...> : public Sequence<Rest...> {
    protected:
      // Reference to the first element of the variadic template.
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

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        FactoryContext* tmp = new FactoryContext();
        ReadResult res = processing(iss, tmp, first(), rest());

        if (res.successes) {
          for (unsigned int i = 0; i < tmp->_children.size(); i++) {
            ctx->add_child(tmp->_children[i]);
          }
          tmp->_children.clear();
        }
        delete tmp;
        return res;
      }

      template<typename F, typename R>
      ReadResult processing(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx, F const* f, R const& r) const {
        
        LOG_DEBUG(_logger, "Processing %s ...", f->get_name().c_str());

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
