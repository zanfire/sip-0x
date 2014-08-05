#if !defined(SIP0X_PROTOCOL_SIPURI_HPP__)
#define SIP0X_PROTOCOL_SIPURI_HPP__

#include <string>
#include <vector>

#include "protocol/HostPort.hpp"

namespace Sip0x
{
  namespace Protocol
  {
    struct SIPURI {

      struct UserInfo {
        std::string username;
        std::string password;

        virtual std::string to_string(void) const {
          if (password.empty()) {
            return username + "@";
          }
          else {
            return username + ":" + password + "@";
          }
        }
      };

      struct Param {
        std::string param;
        std::string value;

        virtual std::string to_string(void) const {
          return param + "=" + value;
        }
      };
      
      bool secure;
      UserInfo userinfo;
      HostPort hostport;
      std::vector<Param> uri_parameters;
      std::vector<Param> headers;


      virtual int write(std::ostream& stream) const {
        return 1;
      }

      virtual std::string to_string(void) const {
        std::string out = "<sip";
        if (secure) {
          out += "s:";
        }
        else {
          out += ":";
        }
        out += userinfo.to_string() + hostport.to_string() + ">" + to_string_uri_parameters(uri_parameters) + to_string_headers(headers);

        return out;
      }

      static std::string to_string_uri_parameters(std::vector<Param> const& params) {
        std::string out;
        for (std::size_t i = 0; i < params.size(); i++) {
          out += ";" + params[i].to_string();
        }
        return out;
      }

      static std::string to_string_headers(std::vector<Param> const& params) {
        std::string out;
        for (std::size_t i = 0; i < params.size(); i++) {
          if (i == 0) {
            out += "?";
          }
          else {
            out += "&";
          }
          out += params[i].to_string();
        }
        return out;
      }
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPURI_HPP__