#if !defined(SIP0X_PARSER_OPERATORS_HPP__)
#define SIP0X_PARSER_OPERATORS_HPP__

#include "parser/base/Alternative.hpp"
#include "parser/base/Occurrence.hpp"
#include "parser/base/Sequence.hpp"


namespace sip0x
{
  namespace Parser
  {
    // Makers

    template <typename... Args>
    Alternative<Args...> make_alternative(Args&&... args) {
      return Alternative<Args...>((args)...);
    }

    template <class T>
    Occurrence<T> make_occurrence(T& t, int min, int max) {
      return Occurrence<T>(t, min, max);
    }

    template <typename... Args>
    Sequence<Args...> make_sequence(Args&&... args) {
      return Sequence<Args...>((args)...);
    }

    // Utils
    
    // Set on all members of a variadic template
    // TODO: implement accepting a lambda 
    template<typename F, typename R>
    void set_parent_variadic(TokenAbstract* parent, F const* f, R const& r) {
      ((F*)f)->set_parent(parent);

      if ((void*)f != (void*)r.first()) {
        set_parent_variadic(parent, r.first(), r.rest());
      }
    }

  }
}

#endif // SIP0X_PARSER_OPERATORS_HPP__
