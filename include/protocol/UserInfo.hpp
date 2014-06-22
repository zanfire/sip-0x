#if !defined(SIP0X_PROTOCOL_USERINFO_HPP__)
#define SIP0X_PROTOCOL_USERINFO_HPP__

#include <string>

namespace Sip0x
{
  namespace Protocol
  {
    struct UserInfo {
      std::string username;
      std::string password;
    };
  }
}

#endif // SIP0X_PROTOCOL_USERINFO_HPP__
