#if !defined(SIP0X_PROTOCOL_SIPMESSAGEHEADER_HPP__)
#define SIP0X_PROTOCOL_SIPMESSAGEHEADER_HPP__

#include <string>

#include "protocol/NameAddr.hpp"

namespace Sip0x
{
  namespace Protocol
  {
    struct SIPMessageHeaderBase {
      virtual std::string param(void) const = 0;
      virtual std::string value(void) const = 0;
      
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
      SIPMethod method;

      virtual std::string param(void) const override { return "CSeq"; }
      virtual std::string value(void) const override { return std::to_string(seq) + " " + convCharsFromSIPMethod(method); }
    };

    struct SIPMessageHeaderMax_Forwards : public SIPMessageHeaderBase {
      unsigned long max = 0;

      virtual std::string param(void) const override { return "Max-Forwards"; }
      virtual std::string value(void) const override { return std::to_string(max); }
    };

    struct SIPMessageHeaderCall_ID : public SIPMessageHeaderBase {
      std::string callID;

      virtual std::string param(void) const override { return "Call-ID"; }
      virtual std::string value(void) const override { return callID;
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

    struct SIPMessageHeaderTo : public SIPMessageHeaderBase {
      NameAddr name_addr;

      virtual std::string param(void) const override { return "To"; }
      virtual std::string value(void) const override { 
        return name_addr.to_string(); 
      }
    };

    //To: Bob <sip:bob@biloxi.com>       
    //Via: SIP/2.0/UDP bobspc.biloxi.com:5060;branch=z9hG4bKnashds7
    //From: Bob <sip:bob@biloxi.com>;tag=456248       
    //Contact: <sip:bob@192.0.2.4> 

  }
}

#endif // SIP0X_PROTOCOL_SIPMESSAGEHEADER_HPP__