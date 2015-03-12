#if !defined(SIP0X_PROTOCOL_SIPREQUEST_HPP__)
#define SIP0X_PROTOCOL_SIPREQUEST_HPP__

#include "protocol/SIPMessage.hpp"
#include "protocol/SIPMethod.hpp"
#include "protocol/SIPURI.hpp"

namespace Sip0x
{
  namespace Protocol
  {

    struct SIPRequest : public SIPMessage {
      SIPMethod method;
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPREQUEST_HPP__
