#if !defined(SIP0X_PROTOCOL_NAMEADDR_HPP__)
#define SIP0X_PROTOCOL_NAMEADDR_HPP__

#include <string>

#include "protocol/SIPURI.hpp"

namespace Sip0x
{
  namespace Protocol
  {
    struct NameAddr {
      std::string displayName;
      SIPURI uri;

      virtual int write(std::ostream& stream) const {
        stream << displayName << '<';
        uri.write(stream);
        stream << '>';
        return 1;
      }

      virtual std::string to_string(void) const {
        if (displayName.empty()) {
          return uri.to_string();
        }
        else {
          return displayName + " " + uri.to_string();
        }
      }
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPVERSION_HPP__