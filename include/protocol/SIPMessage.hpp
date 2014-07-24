#if !defined(SIP0X_PROTOCOL_SIPMESSAGE_HPP__)
#define SIP0X_PROTOCOL_SIPMESSAGE_HPP__

#include <string>
#include <vector>

#include "protocol/SIPURI.hpp"
#include "protocol/SIPMethod.hpp"
#include "protocol/SIPVersion.hpp"
#include "protocol/SIPMessageHeader.hpp"

namespace Sip0x
{
  namespace Protocol
  {
    // Request-Line   =  Method SP Request-URI SP SIP-Version CRLF
    struct RequestLine {
      SIPMethod method;
      SIPURI uri;
      SIPVersion version;
    };

    // Status-Line     =  SIP-Version SP Status-Code SP Reason-Phrase CRLF
    struct StatusLine {
      SIPVersion version;
      int method;
      std::string uri;
    };

    struct SIPMessage {
      std::vector<SIPMessageHeader> headers;
      uint8_t* _content = nullptr;
      int _content_length = 0;
    };

    struct SIPRequest : public SIPMessage {
      RequestLine request;
    };

    struct SIPResponse : public SIPMessage {
      StatusLine status;
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPMESSAGE_HPP__