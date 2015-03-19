#if !defined(SIP0X_PARSER_TOKEN_HPP__)
#define SIP0X_PARSER_TOKEN_HPP__

#include <string>

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/factory/FactoryContext.hpp"

namespace sip0x
{
  namespace parser
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
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* /*ctx*/) const override {
        char c;
        int start = iss.pos();
        for (auto tc : _token) {
          c = iss.get_char();
          if (c != tc) {
            return ParserResult();
          }
        }
         
        return ParserResult(true, start, iss.pos() - start);
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContext();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKEN_HPP__
