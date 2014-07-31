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

    static SIPRequest* create_register(void) {
      SIPRequest* request = new SIPRequest();
      return request;
    }
  }
}

#endif // SIP0X_LOGIC_MESSAGEFACTORY_HPP__
