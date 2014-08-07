#if !defined(SIP0X_PROTOCOL_HOSTPORT_HPP__)
#define SIP0X_PROTOCOL_HOSTPORT_HPP__

#include <string>
#include <vector>

namespace Sip0x
{
  struct HostPort {
    std::string host;
    int port = 0;

    virtual std::string to_string(void) const {
      if (port > 0) {
        return host + ":" + std::to_string(port);
      }
      else {
        return host;
      }
    }
  };
}

#endif // SIP0X_PROTOCOL_HOSTPORT_HPP__