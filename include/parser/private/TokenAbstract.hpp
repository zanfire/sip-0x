#if !defined(SIP0X_PARSER_PARSERABSTRACT_HPP__)
#define SIP0X_PARSER_PARSERABSTRACT_HPP__

#include <tuple>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace Sip0x
{
  namespace Parser
  {
    class TokenAbstract {

    protected:
      //

    public:
      TokenAbstract() {
      }

      virtual ~TokenAbstract(void) {}

      // Read the expected token.
      // returns true if encountered the expected token.  
      virtual std::tuple<bool, void*>  read(std::istringstream& iss) = 0;

      virtual char const* name(void) { return typeid(this).name(); }
    };
  }
}

#endif // SIP0X_PARSER_PARSERABSTRACT_HPP__
