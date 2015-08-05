#if !defined(SIP0X_UTILS_UTILS_HPP__)
#define SIP0X_UTILS_UTILS_HPP__

#include <memory>

namespace sip0x
{
  namespace utils
  {

    ///
    template<class T>
    class enable_protected_dtor {
      friend class deleter;
      
      class deleter {
      public:
        void operator()(T* ptr) { delete ptr; }
      };

    public:
      
      template<typename ... Args>
      static std::shared_ptr<T> create(Args&... rest) {
        return std::shared_ptr<T>(new T(rest...), enable_protected_dtor<T>::deleter());
      }

    protected:
      enable_protected_dtor(void) {}
      virtual ~enable_protected_dtor(void) {}
    };

    std::string trim(const std::string& input);
  }
}

#endif // SIP0X_UTILS_UTILS_HPP__
