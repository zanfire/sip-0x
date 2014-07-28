#if !defined(SIP0X_PROTOCOL_SIPURI_HPP__)
#define SIP0X_PROTOCOL_SIPURI_HPP__

#include <string>
#include <vector>

namespace Sip0x
{
  namespace Protocol
  {
    struct SIPURI {

      struct UserInfo {
        std::string username;
        std::string password;
      };

      struct HostPort {
        std::string host;
        int port;
      };

      struct Param {
        std::string param;
        std::string value;
      };
      
      bool secure;
      UserInfo userinfo;
      HostPort hostport;
      std::vector<Param> uri_parameters;
      std::vector<Param> headers;


      virtual int write(std::ostream& stream) const {
        return 1;
      }
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPURI_HPP__