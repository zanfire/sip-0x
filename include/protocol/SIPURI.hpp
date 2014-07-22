#if !defined(SIP0X_PROTOCOL_SIPMESSAGE_HPP__)
#define SIP0X_PROTOCOL_SIPMESSAGE_HPP__

#include <cstdint>
#include <vector>

#include "protocol/SIPMessageHeader.hpp"

namespace Sip0x
{
  namespace Protocol
  {
    struct SIPMessage {
      std::vector<SIPMessageHeader> headers;
      uint8_t* _content = nullptr;
      int _content_length = 0;
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPMESSAGE_HPP__