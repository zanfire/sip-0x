#if !defined(SIP0X_PARSER_TOKEN_HPP__)
#define SIP0X_PARSER_TOKEN_HPP__

#include <string>

#include "parser/base/TokenAbstract.hpp"

namespace Sip0x
{
  namespace Parser
  {
    /// This parser expects a specific token and return an instance. 
    class Token : public TokenAbstract {

    protected:
    std::string _token;

    public:
      Token(std::string token) : TokenAbstract(), _token(token) {
      }

      virtual ~Token(void) {}

    protected:
      // Read the expected token.
      // returns true if encountered the expected token.  
      virtual ReadResult handle_read(std::istringstream& iss) override {
        std::string expected;
        expected.resize(_token.length() + 1); // size + \0.
        iss.getline(&expected[0], expected.length());
    
        if (expected.compare(0, _token.length(), _token) == 0) {
          iss.ignore(_token.length());
          return ReadResult(true);
        }
        else {
          // abort
          return ReadResult(false);
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKEN_HPP__
