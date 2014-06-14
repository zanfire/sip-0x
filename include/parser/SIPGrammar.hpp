#if !defined(SIP0X_PARSER_PARSERBASE_HPP__)
#define SIP0X_PARSER_SIPGRAMMAR_HPP__

#include <string>

namespace Sip0x 
{
  namespace Parser
  {
    class SIPGrammar {
    protected:
      
    public:
      SIPGrammar(void) {
        // nop
      }

      virtual ~SIPGrammar(void) {

      }

      // TODO: Returns a context with the result and the SIP Message.
      bool parse(std::string& message) {
        return false; // _root.parse(message);
      }
    };
  }
}

#endif // SIP0X_PARSER_PARSERBASE_HPP__
