#if !defined(SIP0X_PROTOCOL_SIPMESSAGEHEADER_HPP__)
#define SIP0X_PROTOCOL_SIPMESSAGEHEADER_HPP__

#include <string>

namespace Sip0x
{
  namespace Protocol
  {
    struct SIPMessageHeader {
      std::string name;
      std::string value;
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPMESSAGEHEADER_HPP__