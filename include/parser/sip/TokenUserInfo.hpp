#if !defined(SIP0X_PARSER_TOKENUSERINFO_HPP__)
#define SIP0X_PARSER_TOKENUSERINFO_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/common/RegexConstStrings.hpp"

#include "protocol/UserInfo.hpp"

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
      // it is magic ... no is nested template.
      Sequence<TokenRegex, Occurrence<Sequence<Token, TokenRegex>>, Token> _sequence;
      
    public:
      TokenUserInfo(void) : 
        // Writing down the ABN for userinfo.
            _sequence(
            TokenRegex("username", "(" + RegexConstStrings::unreserved + "|" + RegexConstStrings::escaped + "|" + RegexConstStrings::sip_user_unreserved + ")+"), 
            Occurrence<Sequence<Token, TokenRegex>>
            (
              Sequence<Token, TokenRegex>
              (
                Token(":"),
                TokenRegex("password", "(" + RegexConstStrings::unreserved + "|" + RegexConstStrings::escaped + "|" + RegexConstStrings::sip_password_unreserved + ")*")
              ), 
            0, 1),
            Token("@")
        ) 
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenUserInfo");
        _name = "TokenUserInfo";
        // User.

        // We must create a resulting object during the parsing procedure
        _sequence.set_parent(this);
      }

      virtual ~TokenUserInfo(void) {
      }

    protected:
      virtual ReadResult handle_read(std::istringstream& iss, void* ctx) const override {
        // If we create some instance hear we need to kept some sort of syncronization because it coldn't be used 
        // concurrently avoiding mutex.
        Sip0x::Protocol::UserInfo* ui = new Sip0x::Protocol::UserInfo();
        ReadResult r = _sequence.read(iss, ui);
        if (r.successes) {
          r.result = ui;
          r.result_dtor = [](void* p) {
            Sip0x::Protocol::UserInfo* ui = (Sip0x::Protocol::UserInfo*)p;
            delete ui;
          };
        }
        else {
          delete ui;
        }
        return r;
      }

      virtual void handle_on_success(TokenAbstract const* token, ReadResult const& result, void* ctx) override {
        Sip0x::Protocol::UserInfo* ui = (Sip0x::Protocol::UserInfo*)ctx;
        DEBUG(_logger, "Successed parsed token: \"%s\", result: \"%s\".", token->get_name().c_str(), result.parsed.c_str());;
        if (token->get_name().compare("username") == 0) {
          //std::cout << "username: " << result.parsed << std::endl;
          ui->username = result.parsed;
        }
        else if (token->get_name().compare("password") == 0) {
          //std::cout << "password: " << result.parsed << std::endl;
          ui->password = result.parsed;
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENIPV6_HPP__
