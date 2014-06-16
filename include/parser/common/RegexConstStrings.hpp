#if !defined(SIP0X_PARSER_REGEXCONSTSTRINGS_HPP__)
#define SIP0X_PARSER_REGEXCONSTSTRINGS_HPP__

#include "parser/base/TokenAbstract.hpp"

#include <string>

namespace Sip0x
{
  namespace Parser
  {
    struct RegexConstStrings {
      const static std::string unreserved;
      const static std::string escaped;

      const static std::string sip_user_unreserved;
      const static std::string sip_password_unreserved;
    };


    const std::string RegexConstStrings::unreserved = "([A-Za-z-0-9]|[-_\\.\\!\\~\\*\\'\\|])";
    const std::string RegexConstStrings::escaped = "(%[0-9a-fA-F][0-9a-fA-F])";

    const std::string RegexConstStrings::sip_user_unreserved = "([\\&=\\+\\$,;\\?/])";
    const std::string RegexConstStrings::sip_password_unreserved = "([\\&=\\+\\$,])";
  }
}

#endif // SIP0X_PARSER_REGEXCONSTSTRINGS_HPP__
