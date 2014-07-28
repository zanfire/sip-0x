#if !defined(SIP0X_PROTOCOL_SIPMESSAGE_HPP__)
#define SIP0X_PROTOCOL_SIPMESSAGE_HPP__

#include <string>
#include <vector>
#include <ostream>

#include "protocol/SIPURI.hpp"
#include "protocol/SIPMethod.hpp"
#include "protocol/SIPVersion.hpp"
#include "protocol/SIPMessageHeader.hpp"

namespace Sip0x
{
  namespace Protocol
  {
  
    struct SIPMessage {
      std::vector<SIPMessageHeader> headers;
      std::vector<uint8_t> _content;
      
      virtual int write(std::ostream& stream) const {
        for (auto h : headers) {
          //h.
        }
        stream.write("\r\n", 2);
        for (auto c : _content) {
          stream.put(c);
        }
        return 1;
      }
    };

    struct SIPRequest : public SIPMessage {
      SIPMethod method;
      SIPURI uri;
      SIPVersion version;

      virtual int write(std::ostream& stream) const override {
        char const* m = convCharsFromSIPMethod(method);
        stream.write(m, strlen(m));
        stream.put(' ');
        uri.write(stream);
        stream.put(' ');
        version.write(stream);
        stream.write("\r\n", 2);

        return SIPMessage::write(stream);
      }
    };

    struct SIPResponse : public SIPMessage {
      SIPVersion version;
      int status_code;
      std::string reason_phrase;
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPMESSAGE_HPP__