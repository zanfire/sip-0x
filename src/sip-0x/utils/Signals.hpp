#if !defined(SIP0X_UTILS_SIGNALS_HPP__)
#define SIP0X_UTILS_SIGNALS_HPP__

#include <memory>
#include <vector>

//! These are a set of classes for the signal slot pattern implementation.
//! - Signal
//! - Slot
namespace sip0x
{
  namespace utils
  {
    // Forward declaration.
    template<class... Args> class Event;

    class BaseDelegate {
    public:
      BaseDelegate(void) = default;
      virtual ~BaseDelegate(void) = default;
    };

    template<class... Args> class AbstractDelegate : public BaseDelegate
    {
    protected:
      virtual ~AbstractDelegate();

      friend class Event<Args...>;

      void add(Event<Args...> *s){ v.push_back(s); }
      void remove(Event<Args...> *s){ v.erase(std::remove(v.begin(), v.end(), s), v.end()); }

      virtual void call(Args... args) = 0;

      std::vector<Event<Args...>*> v;
    };

    template<class T, class... Args> class ConcreteDelegate : public AbstractDelegate<Args...>
    {
    public:
      ConcreteDelegate(T *t, void(T::*f)(Args...), Event<Args...> &s);

    private:
      ConcreteDelegate(const ConcreteDelegate&);
      void operator=(const ConcreteDelegate&);

      friend class Event<Args...>;

      virtual void call(Args... args){ (t->*f)(args...); }

      T *t;
      void(T::*f)(Args...);
    };

    template<class... Args> class Event
    {
    public:
      Event(){ }
      ~Event(){ for (auto i : v) i->remove(this); }

      void connect(AbstractDelegate<Args...> &s){ v.push_back(&s); s.add(this); }
      void disconnect(AbstractDelegate<Args...> &s){ v.erase(std::remove(v.begin(), v.end(), &s), v.end()); }

      void emit(Args... args){ for (auto i : v) i->call(args...); }

    private:
      Event(const Event&);
      void operator=(const Event&);

      std::vector<AbstractDelegate<Args...>*> v;
    };

    template<class... Args> AbstractDelegate<Args...>::~AbstractDelegate()
    {
      for (auto i : v) i->disconnect(*this);
    }

    template<class T, class... Args> ConcreteDelegate<T, Args...>::ConcreteDelegate(T *t, void(T::*f)(Args...), Event<Args...> &s) : t(t), f(f)
    {
      s.connect(*this);
    }

    class Delegate
    {
    public:
      Delegate(){ }
      ~Delegate(){ for (auto i : v) delete i; }

      template<class T, class... Args> void connect(T *t, void(T::*f)(Args...), Event<Args...> &s){ v.push_back(new ConcreteDelegate<T, Args...>(t, f, s)); }

    private:
      Delegate(const Delegate&);
      void operator=(const Delegate&);

      std::vector<BaseDelegate*> v;
    };
  }
}

#endif // SIP0X_UTILS_SIGNALS_HPP__
