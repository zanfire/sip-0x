#if !defined(SIP0X_PARSER_OPERATORS_HPP__)
#define SIP0X_PARSER_OPERATORS_HPP__

#include "parser/base/OpAbstract.hpp"

#include "parser/base/Alternative.hpp"
#include "parser/base/Occurrence.hpp"
#include "parser/base/Sequence.hpp"


namespace Sip0x
{
  namespace Parser
  {
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
  }
}

#endif // SIP0X_PARSER_OPERATORS_HPP__
