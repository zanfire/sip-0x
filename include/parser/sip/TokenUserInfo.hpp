#if !defined(SIP0X_PARSER_TOKENUSERINFO_HPP__)
#define SIP0X_PARSER_TOKENUSERINFO_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/OpSequence.hpp"
#include "parser/base/OpOccurrence.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/common/RegexConstStrings.hpp"

// unreserved = alphanum / mark
// mark = "-" / "_" / "." / "!" / "~" / "*" / "'" / "(" / ")"

// ABNF
// userinfo         =  ( user / telephone-subscriber ) [ ":" password ] "@"
// user             =  1*( unreserved / escaped / user-unreserved )
// user-unreserved  =  "&" / "=" / "+" / "$" / "," / ";" / "?" / "/"
// password         =  *( unreserved / escaped / "&" / "=" / "+" / "$" / "," )

namespace Sip0x
{
  namespace Parser
  {
    class TokenUserInfo : public TokenAbstract {

    protected:
      OpSequence _sequence;

    public:
      TokenUserInfo(void) : TokenAbstract() {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenUserInfo");
        _name = "TokenUserInfo";
        // User.
        // unreserved ([A-Za-z-0-9]|(\-_|\.|\!|\~|\*|\'|\|))+
        // escaped (%[0-9a-fA-F][0-9a-fA-F])
        // user-unreserved (&|=|\\+|\\$|,|;|\\?|/|)
        _sequence.add_regex("user", "(" + RegexConstStrings::unreserved + "|" + RegexConstStrings::escaped + "|"  + RegexConstStrings::sip_user_unreserved + ")+");
        // Password.
        OpSequence* password = new OpSequence();
        password->add_token(":");
        password->add_regex("password", "(" + RegexConstStrings::unreserved + "|" + RegexConstStrings::escaped + "|"  + RegexConstStrings::sip_password_unreserved + ")*");
        _sequence.add_occurrence("password", std::shared_ptr<TokenAbstract>(password), 0, 1);
        // @
        _sequence.add_token("@");
      }

      virtual ~TokenUserInfo(void) {
      }

    protected:
      virtual ReadResult handle_read(std::istringstream& iss) const override {
        return _sequence.handle_read(iss);
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENIPV6_HPP__
