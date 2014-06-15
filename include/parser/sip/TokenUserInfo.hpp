#if !defined(SIP0X_PARSER_TOKENUSERINFO_HPP__)
#define SIP0X_PARSER_TOKENUSERINFO_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/OpSequence.hpp"
#include "parser/base/OpOccurrence.hpp"
#include "parser/base/TokenRegex.hpp"


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
        // User.
        _sequence.add_regex("[a-z]*");
        // Password.
        OpSequence* password = new OpSequence();
        password->add_token(":");
        password->add_regex("[a-z]*");
        _sequence.add_occurrence(std::shared_ptr<TokenAbstract>(password), 0, 1);
        // @
        _sequence.add_token("@");
      }

      virtual ~TokenUserInfo(void) {
      }

    protected:
      virtual ReadResult handle_read(std::istringstream& iss) override {
        return _sequence.handle_read(iss);
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENIPV6_HPP__
