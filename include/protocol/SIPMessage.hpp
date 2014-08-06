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
  
    class SIPMessage {
    public:
      std::vector<std::shared_ptr<SIPMessageHeaderBase>> headers;
      std::vector<uint8_t> content;
      
      virtual int write(std::ostream& stream) const {
        for (auto h : headers) {
          h->write(stream);
        }
        stream.write("\r\n", 2);
        for (auto c : content) {
          stream.put(c);
        }
        return 1;
      }
    };

    class SIPRequest : public SIPMessage {
    public:
      SIPMethod method;
      SIPURI uri;
      SIPVersion version;

      virtual int write(std::ostream& stream) const override {
        stream << convCharsFromSIPMethod(method) << ' ' << uri.to_string();
        stream << ' ';
        version.write(stream);
        stream << "\r\n";

        return SIPMessage::write(stream);
      }
    };

    class SIPResponse : public SIPMessage {
    public:
      SIPVersion version;
      int status_code;
      std::string reason_phrase;

      virtual int write(std::ostream& stream) const override {
        version.write(stream);
        stream.put(' ');
        stream << status_code;
        stream.put(' ');
        stream << reason_phrase;
        stream.write("\r\n", 2);

        return SIPMessage::write(stream);
      }
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPMESSAGE_HPP__