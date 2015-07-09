#if !defined(SIP0X_UTILS_CLOCK_HPP__)
#define SIP0X_UTILS_CLOCK_HPP__

#include <chrono>

namespace sip0x
{
  namespace utils {
    //! This is an helper class that wrap the steady clock. 
    //! This class provide the ability to fake time for testing.
    struct Clock {
    private:
      //! Custom offset for faking time. 
      static long long _offset;
    private:
      Clock(void) = default;
      ~Clock(void) = default;
    public:
      //! Enable the fake time adding an offset of milliseconds. 
      //! \remark this code is NOT thread-safe.
      static void add_offset(long long millis) { _offset += millis; }
      static long long offset(void) { return _offset; }

      //! \returns the time passed in milliseconds.
      //! \remarks Source of this clock could be faked for testing purpose.
      static long long now_millis(void) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() + _offset;
      }
    };
  }
}

#endif // SIP0X_UTILS_CLOCK_HPP__
