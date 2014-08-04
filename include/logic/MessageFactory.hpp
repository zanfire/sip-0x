#if !defined(SIP0X_LOGIC_MESSAGEFACTORY_HPP__)
#define SIP0X_LOGIC_MESSAGEFACTORY_HPP__

#include "protocol/SIP.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"
#include "utils/InputTokenStream.hpp"

namespace Sip0x
{
  namespace Logic
  {
    using namespace Sip0x::Utils::Log;
    using namespace Sip0x::Protocol;

    static SIPRequest create_register(void) {
      /*
      REGISTER sip:registrar.biloxi.com SIP/2.0
      Via: SIP/2.0/UDP bobspc.biloxi.com:5060;branch=z9hG4bKnashds7
      Max-Forwards: 70       
      To: Bob <sip:bob@biloxi.com>       
      From: Bob <sip:bob@biloxi.com>;tag=456248       
      Call-ID: 843817637684230@998sdasdh09 
      CSeq: 1826 REGISTER       
      Contact: <sip:bob@192.0.2.4> 
      Expires: 7200       
      Content-Length: 0
      */
      SIPRequest request;
      request.method = SIPMethod::SIPMETHOD_REGISTER;
      request.version.major = 2;
      request.headers.
      return request;
    }
  }
}

#endif // SIP0X_LOGIC_MESSAGEFACTORY_HPP__
