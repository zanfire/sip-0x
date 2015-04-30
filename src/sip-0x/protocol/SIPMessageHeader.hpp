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
      virtual SIPMessageHeaderBase* clone(void) const = 0;

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

      virtual std::string param(void) const override { return _name; }
      virtual std::string value(void) const override { return _value; }
      virtual SIPMessageHeaderBase* clone(void) const override {
        SIPMessageHeaderGeneric* c = new SIPMessageHeaderGeneric();
        c->_name = _name;
        c->_value = _value;
        return c;
      }
    };

    struct SIPMessageHeaderCSeq : public SIPMessageHeaderBase {
      unsigned long seq;
      protocol::SIPMethod method;

      virtual std::string param(void) const override { return "CSeq"; }
      virtual std::string value(void) const override { return std::to_string(seq) + " " + protocol::convCharsFromSIPMethod(method); }
      virtual SIPMessageHeaderBase* clone(void) const override {
        SIPMessageHeaderCSeq* c = new SIPMessageHeaderCSeq();
        c->seq = seq;
        c->method = method;
        return c;
      }
    };

    struct SIPMessageHeaderMax_Forwards : public SIPMessageHeaderBase {
      unsigned long max = 0;

      virtual std::string param(void) const override { return "Max-Forwards"; }
      virtual std::string value(void) const override { return std::to_string(max); }
      virtual SIPMessageHeaderBase* clone(void) const override {
        SIPMessageHeaderMax_Forwards* c = new SIPMessageHeaderMax_Forwards();
        c->max = max;
        return c;
      }
    };

    struct SIPMessageHeaderCall_ID : public SIPMessageHeaderBase {
      std::string callID;

      virtual std::string param(void) const override { return "Call-ID"; }
      virtual std::string value(void) const override { return callID; }
      virtual SIPMessageHeaderBase* clone(void) const override {
        SIPMessageHeaderCall_ID* c = new SIPMessageHeaderCall_ID();
        c->callID = callID;
        return c;
      }
    };

    struct SIPMessageHeaderExpires : public SIPMessageHeaderBase {
      unsigned long expires = 0;

      virtual std::string param(void) const override { return "Expires"; }
      virtual std::string value(void) const override { return std::to_string(expires); }
      virtual SIPMessageHeaderBase* clone(void) const override {
        SIPMessageHeaderExpires* c = new SIPMessageHeaderExpires();
        c->expires = expires;
        return c;
      }
    };

    struct SIPMessageHeaderContent_Length : public SIPMessageHeaderBase {
      unsigned long length = 0;

      virtual std::string param(void) const override { return "Content-Length"; }
      virtual std::string value(void) const override { return std::to_string(length); }
      virtual SIPMessageHeaderBase* clone(void) const override {
        SIPMessageHeaderContent_Length* c = new SIPMessageHeaderContent_Length();
        c->length = length;
        return c;
      }
    };

    struct SIPMessageHeaderWithNameAddr : public SIPMessageHeaderBase {
      NameAddr name_addr;
      std::vector<std::pair<std::string, std::string>> params;

      virtual std::string value(void) const override { return name_addr.to_string() + to_string_params(params); }

      static std::string to_string_params(std::vector<std::pair<std::string, std::string>> const& params) {
        std::string out;
        for (auto p : params) {
          out += ";" + p.first + "=" + p.second;
        }
        return out;
      }

    protected:
      void copy_to(SIPMessageHeaderWithNameAddr* to) const {
        to->name_addr.displayName = name_addr.displayName;
        to->name_addr.uri = name_addr.uri;
        for (auto p : params) {
          to->params.push_back(std::make_pair(p.first, p.second));
        }
      }
    };

    struct SIPMessageHeaderTo : public SIPMessageHeaderWithNameAddr {
      virtual std::string param(void) const override { return "To"; }
      virtual SIPMessageHeaderBase* clone(void) const override {
        SIPMessageHeaderTo* c = new SIPMessageHeaderTo();
        copy_to(c);
        return c;
      }
    };

    struct SIPMessageHeaderFrom : public SIPMessageHeaderWithNameAddr {
      virtual std::string param(void) const override { return "From"; }
      virtual SIPMessageHeaderBase* clone(void) const override {
        SIPMessageHeaderFrom* c = new SIPMessageHeaderFrom();
        copy_to(c);
        return c;
      }
    };

    struct SIPMessageHeaderContact : public SIPMessageHeaderWithNameAddr {
      virtual std::string param(void) const override { return "Contact"; }
      virtual SIPMessageHeaderBase* clone(void) const override {
        SIPMessageHeaderContact* c = new SIPMessageHeaderContact();
        copy_to(c);
        return c;
      }
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

      virtual SIPMessageHeaderBase* clone(void) const override {
        SIPMessageHeaderVia* c = new SIPMessageHeaderVia();
        c->protocol = protocol;
        c->version = version;
        c->transport = transport;
        c->hostport.host = hostport.host; 
        c->hostport.port = hostport.port;
        for (auto p : params) {
          c->params.push_back(std::make_pair(p.first, p.second));
        }
        return c;
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
      virtual std::string value(void) const override { return user_agent; }
      virtual SIPMessageHeaderBase* clone(void) const override {
        SIPMessageHeaderUser_Agent* c = new SIPMessageHeaderUser_Agent();
        c->user_agent = user_agent;
        return c;
      }
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPMESSAGEHEADER_HPP__