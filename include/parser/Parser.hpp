#if !defined(SIP0X_PARSER_PARSER_HPP__)
#define SIP0X_PARSER_PARSER_HPP__


#include <iostream>
#include <string>
#include <vector>

namespace Sip0x 
{
  namespace Parser 
  {
    class ParserX {
    public:
      ParserX(void);
      virtual ~ParserX(void);

      // TODO: Add usage of tuiple.
      bool parse(std::string message);
    };
  }
}

#endif // SIP0X_PARSER_PARSER_HPP__
