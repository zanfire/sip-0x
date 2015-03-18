#if !defined(SIP0X_PARSER_ALTERNATIVE_HPP__)
#define SIP0X_PARSER_ALTERNATIVE_HPP__

#include "parser/tokens/TokenAbstract.hpp"

namespace sip0x
{
  namespace parser
  {
    // Generic definition.
    template<typename... Arguments>
    class Alternative;

    // Base definition.
    template<typename First>
    class Alternative<First> : public TokenAbstract {

    protected:
      First member;

    public:
      Alternative(First& f) : TokenAbstract("Alternative"), member(f) {
#if defined(ENABLE_PARSER_LOGGING)
        _logger = LoggerFactory::get_logger("sip0x.Parser.Alternative");
#endif
        _name += "..." + f.get_name();
      }

      virtual ~Alternative(void) {}

      First const* first(void) const {
        return &member;
      }
      
      Alternative<First> const& rest(void) const {
        return *this;
      }

      //virtual FactoryContext* create_factory(void) const override {
      //  return nullptr;
      //}
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
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        FactoryContext* tmp = new FactoryContext();
        ParserResult res = processing(iss, tmp, first(), rest());

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
      ParserResult processing(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx, F const* f, R const& r) const {
#if defined(ENABLE_PARSER_LOGGING)
        LOG_DEBUG(_logger, "Processing %s ...", f->get_name().c_str());
#endif
        ParserResult result = f->read(iss, ctx);
        if (result.successes) {
#if defined(ENABLE_PARSER_LOGGING)
          LOG_DEBUG(_logger, "Alternative %s successes.", f->get_name().c_str());
#endif
          return result;
        }
        
        if ((void*)f != (void*)r.first()) {
          return processing(iss, ctx, r.first(), r.rest());
        }
        else {
#if defined(ENABLE_PARSER_LOGGING)
          LOG_DEBUG(_logger, "No alternative parsed correctly.");
#endif
          return ParserResult(false);
        }

      }
    };
  }
}

#endif // SIP0X_PARSER_ALTERNATIVE_HPP__
