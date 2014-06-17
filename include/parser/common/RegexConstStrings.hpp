#if !defined(SIP0X_PARSER_REGEXCONSTSTRINGS_HPP__)
#define SIP0X_PARSER_REGEXCONSTSTRINGS_HPP__

#include "parser/base/TokenAbstract.hpp"

#include <string>

namespace Sip0x
{
  namespace Parser
  {
    struct RegexConstStrings {
      /*
      token       =  1*(alphanum / "-" / "." / "!" / "%" / "*"
                     / "_" / "+" / "`" / "'" / "~" )
      separators  =  "(" / ")" / "<" / ">" / "@" /
                     "," / ";" / ":" / "\" / DQUOTE /
                     "/" / "[" / "]" / "?" / "=" /
                     "{" / "}" / SP / HTAB
      word        =  1*(alphanum / "-" / "." / "!" / "%" / "*" /
                     "_" / "+" / "`" / "'" / "~" /
                     "(" / ")" / "<" / ">" /
                     ":" / "\" / DQUOTE /
                     "/" / "[" / "]" / "?" /
                     "{" / "}" )
      */
      const static std::string token;
      //const static std::string separators;
      //const static std::string word;

      const static std::string unreserved;
      const static std::string escaped;

      const static std::string sip_user_unreserved;
      const static std::string sip_password_unreserved;
      const static std::string sip_param_unreserved;
    };

    const std::string RegexConstStrings::token = "([A-Za-z-0-9\\-_\\.\\!\\%\\*\\+`\\'\\~]+)";

    const std::string RegexConstStrings::unreserved = "([A-Za-z-0-9]|[\\-_\\.\\!\\~\\*\\'\\|])";
    const std::string RegexConstStrings::escaped = "(%[0-9a-fA-F][0-9a-fA-F])";

    const std::string RegexConstStrings::sip_user_unreserved = "([\\&=\\+\\$,;\\?/])";
    const std::string RegexConstStrings::sip_password_unreserved = "([\\&=\\+\\$,])";

    const std::string RegexConstStrings::sip_param_unreserved = "([\\[\\]/\\:\\&\\+\\$])";
  }
}

#endif // SIP0X_PARSER_REGEXCONSTSTRINGS_HPP__
