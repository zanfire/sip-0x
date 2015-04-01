#if !defined(SIP0X_PROTOCOL_SIPMESSAGEHEADER_HPP__)
#define SIP0X_PROTOCOL_SIPMESSAGEHEADER_HPP__

#include <string>

#include "protocol/NameAddr.hpp"

namespace sip0x
{
  namespace protocol {
    struct SIPMessageHeaderBase {
      virtual std::string param(void) const = 0;
      virtual std::string value(void) const = 0;

      virtual std::string to_string(void) const {
        return param() + ": " + value() + "\r\n";
      }

      virtual int write(std::ostream& stream) const {
        stream << param() << ": " << value() << "\r\n";
        return 1;
      }
    };


    struct SIPMessageHeaderGeneric : public SIPMessageHeaderBase {
      std::string _name;
      std::string _value;

      SIPMessageHeaderGeneric(void) {}

      virtual std::string param(void) const override { return _name.c_str(); }
      virtual std::string value(void) const override { return _value.c_str(); }
    };

    struct SIPMessageHeaderCSeq : public SIPMessageHeaderBase {
      unsigned long seq;
      protocol::SIPMethod method;

      virtual std::string param(void) const override { return "CSeq"; }
      virtual std::string value(void) const override { return std::to_string(seq) + " " + protocol::convCharsFromSIPMethod(method); }
    };

    struct SIPMessageHeaderMax_Forwards : public SIPMessageHeaderBase {
      unsigned long max = 0;

      virtual std::string param(void) const override { return "Max-Forwards"; }
      virtual std::string value(void) const override { return std::to_string(max); }
    };

    struct SIPMessageHeaderCall_ID : public SIPMessageHeaderBase {
      std::string callID;

      virtual std::string param(void) const override { return "Call-ID"; }
      virtual std::string value(void) const override {
        return callID;
      }
    };

    struct SIPMessageHeaderExpires : public SIPMessageHeaderBase {
      unsigned long expires = 0;

      virtual std::string param(void) const override { return "Expires"; }
      virtual std::string value(void) const override { return std::to_string(expires); }
    };

    struct SIPMessageHeaderContent_Length : public SIPMessageHeaderBase {
      unsigned long length = 0;

      virtual std::string param(void) const override { return "Content-Length"; }
      virtual std::string value(void) const override { return std::to_string(length); }
    };

    struct SIPMessageHeaderWithNameAddr : public SIPMessageHeaderBase {
      NameAddr name_addr;
      std::vector<std::pair<std::string, std::string>> params;

      virtual std::string value(void) const override {
        return name_addr.to_string() + to_string_params(params);
      }

      static std::string to_string_params(std::vector<std::pair<std::string, std::string>> const& params) {
        std::string out;
        for (auto p : params) {
          out += ";" + p.first + "=" + p.second;
        }
        return out;
      }
    };

    struct SIPMessageHeaderTo : public SIPMessageHeaderWithNameAddr {
      virtual std::string param(void) const override { return "To"; }
    };

    struct SIPMessageHeaderFrom : public SIPMessageHeaderWithNameAddr {
      virtual std::string param(void) const override { return "From"; }
    };

    struct SIPMessageHeaderContact : public SIPMessageHeaderWithNameAddr {
      virtual std::string param(void) const override { return "Contact"; }
    };

    //Via: SIP/2.0/UDP bobspc.biloxi.com:5060;branch=z9hG4bKnashds7 
    struct SIPMessageHeaderVia : public SIPMessageHeaderBase {
      std::string protocol;
      std::string version;
      std::string transport;
      HostPort hostport;
      std::vector<std::pair<std::string, std::string>> params;

      virtual std::string param(void) const override { return "Via"; }
      virtual std::string value(void) const override {
        return protocol + "/" + version + "/" + transport + " " + hostport.to_string() + to_string_params(params);
      }

      static std::string to_string_params(std::vector<std::pair<std::string, std::string>> const& params) {
        std::string out;
        for (auto p : params) {
          out += ";" + p.first + "=" + p.second;
        }
        return out;
      }
    };

    struct SIPMessageHeaderUser_Agent : public SIPMessageHeaderBase {
      std::string user_agent;

      virtual std::string param(void) const override { return "User-Agent"; }
      virtual std::string value(void) const override {
        return user_agent;
      }
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPMESSAGEHEADER_HPP__