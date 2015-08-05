#if !defined(SIP0X_UTILS_THREADEDOBJECT_HPP__)
#define SIP0X_UTILS_THREADEDOBJECT_HPP__

#include <memory>
#include <thread>

namespace sip0x
{
  namespace utils
  {
    //! Base class that provided an implementation of a single thread creation.
    //!
    //! The derived class must implement process method and read the member _thread_must_stop. This member means 
    //! when process implementation must exit from processing loop.
    class ThreadedObject {
    protected:
      std::thread* _thread = nullptr;
      bool _thread_must_stop = false;

    public:
      ThreadedObject(void) {}
      virtual ~ThreadedObject(void) {
        stop();
        delete _thread;
      }

      //! Start and create thread object. 
      void start(void) {
        if (_thread == nullptr) {
          _thread = new std::thread([this](){ process(); });
        }
      }

      //! Stop and destroy thread. Process implementation must be aware of _thread_must_stop member.
      void stop(void) {
        if (_thread != nullptr) {
          _thread_must_stop = true;
          if (_thread->joinable())_thread->join();
          delete _thread;
          _thread = nullptr;
        }
      }

      virtual void process(void) = 0;
    };
  }
}

#endif // SIP0X_UTILS_THREADEDOBJECT_HPP__
