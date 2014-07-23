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
      Token(std::string token) : TokenAbstract(token), _token(token) {
      }

      virtual ~Token(void) {}

    protected:
      // Read the expected token.
      // returns true if encountered the expected token.  
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        char c;
        for (auto tc : _token) {
          c = iss.get_char();
          if (c != tc) {
            return ReadResult(false);
          }
        }
         
        return ReadResult(true);
      }

      virtual FactoryContext* create_factory(FactoryContext* factory) const override {
        return new FactoryContext();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKEN_HPP__
