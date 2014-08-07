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
    using namespace Sip0x;

    //! Returns first occurrence of type T. If is not present in header vector it will be added.
    
    template<typename T>
    static std::shared_ptr<T> get_first_occurrence(SIPMessage* message) {
      // Search and returns the first occurrence.
      for (auto h : message->headers) {
        T* cast = dynamic_cast<T*>(h.get());
        if (cast != nullptr) {
          // Found
          return cast
        }
      }
      return nullptr;
    }

  }
}

#endif // SIP0X_LOGIC_MESSAGEFACTORY_HPP__
