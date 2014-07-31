#if !defined(SIP0X_UTILS_LISTENERS_HPP__)
#define SIP0X_UTILS_LISTENERS_HPP__

#include <string>
#include <map>
#include <mutex>

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"

namespace Sip0x
{
  namespace Utils
  {
    using namespace Sip0x::Utils::Log;

    // Observer impl.
    template <class Type>
    class Listeners {

    private:
      std::shared_ptr<Logger> _logger;

      std::recursive_mutex _mtx;
      bool _notifying;
      std::set<Type> _pendingRemoval;
      std::set<Type> _pendingAddition;
      std::set<Type> _listeners;

    public:
      Listeners(void) {
        _logger = LoggerManager::get_logger("Sip0x.Utils.Listeners");
      }

      virtual ~Listeners(void) {
      }

      void add(Type listener) {
        std::lock_guard<std::recursive_mutex> lock(_mtx);

        if (_notifying) {
          _pendingAddition.insert(listener);
          _pendingRemoval.erase(listener);
        }
        else {
          _listeners.insert(listener);
        }
      }

      void remove(Type listener) {
        std::lock_guard<std::recursive_mutex> lock(_mtx);

        if (_notifying) {
          _pendingRemoval.insert(listener);
          _pendingAddition.erase(listener);
        }
        else {
          m_listeners.erase(listener);
        }
      }

      template <class Function, class... Arguments>
      inline void notify(Function&& f, Arguments&&... args) {
        std::lock_guard<std::recursive_mutex> lock(_mtx);

        _notifying = true;
        for (Type listener : _listeners) {
          auto callback = std::bind(f, listener, args...);
          callback(listener);
        }
        _notifying = false;

        // Remove pending.
        for (Type listener : _pendingRemoval) {
          m_listeners.erase(listener);
        }
        _pendingRemoval.clear();
        // Add pending.
        for (Type listener : _pendingAddition) {
          _listeners.insert(listener);
        }
        _pendingAddition.clear();
      }

    };
  }
}
 

#endif // SIP0X_UTILS_LISTENERS_HPP__
