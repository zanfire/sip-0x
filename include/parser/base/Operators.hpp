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


    template <typename... Args>
    Occurrence<Args...> make_occurrence(Args&&... args) {
      return Occurrence<Args...>((args)...);
    }

    template <typename... Args>
    Sequence<Args...> make_sequence(Args&&... args) {
      return Sequence<Args...>((args)...);
    }
  }
}

#endif // SIP0X_PARSER_OPERATORS_HPP__
