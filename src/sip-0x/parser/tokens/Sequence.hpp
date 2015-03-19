#if !defined(SIP0X_PARSER_SEQUENCE_HPP__)
#define SIP0X_PARSER_SEQUENCE_HPP__

#include "parser/tokens/TokenAbstract.hpp"

namespace sip0x
{
  namespace parser
  {
    /// 

    // Generic definition.
    template<typename... Arguments>
    class Sequence;

    // Base definition.
    template<typename First>
    class Sequence<First> : public TokenAbstract {

    protected:
      First member;
      bool _disable_factory;

    public:
      Sequence(First f) : TokenAbstract("Sequence"), member(f) {
#if defined(ENABLE_PARSER_LOGGING)
        _logger = LoggerFactory::get_logger("sip0x.Parser.Sequence");
#endif
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
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        FactoryContext* tmp = new FactoryContext();
        ParserResult res = processing(iss, tmp, first(), rest());

        if (res.success()) {
          for (unsigned int i = 0; i < tmp->_children.size(); i++) {
            ctx->add_child(tmp->_children[i]);
          }
          tmp->_children.clear();
        }
        delete tmp;
        return res;
      }

      template<typename F, typename R>
      ParserResult processing(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx, F const* f, R const& r) const {
#if defined(ENABLE_PARSER_LOGGING)
        LOG_DEBUG(_logger, "Processing %s ...", f->get_name().c_str());
#endif

        ParserResult result = f->read(iss, ctx);
        if (!result.success()) {
          result.push_event(ParserResult::TYPE_ERROR, iss.pos(), "Expected token " + f->get_name());
          return result;
        }
      
        if ((void*)f != (void*)r.first()) {
          return processing(iss, ctx, r.first(), r.rest());
        }
        else {
          return ParserResult(true, 0, 0);
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_SEQUENCE_HPP__
