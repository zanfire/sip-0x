#if !defined(SIP0X_UTILS_SIGNALS_HPP__)
#define SIP0X_UTILS_SIGNALS_HPP__

#include <memory>
#include <vector>

//! This module implement the Signal/Slot pattern.
//! \usage Classes must define a Signal that must be connected with a slot.

//! - Signal
//! - Slot
namespace sip0x
{
  namespace utils
  {
    // Forward declaration.
    template<class... Args> class Signal;

    class BaseSlot {
    public:
      BaseSlot(void) = default;
      virtual ~BaseSlot(void) = default;
    };

    template<class... Args> class AbstractSlot : public BaseSlot
    {
    protected:
      virtual ~AbstractSlot();

      friend class Signal<Args...>;

      void add(Signal<Args...> *s){ v.push_back(s); }
      void remove(Signal<Args...> *s){ v.erase(std::remove(v.begin(), v.end(), s), v.end()); }

      virtual void call(Args... args) = 0;

      std::vector<Signal<Args...>*> v;
    };

    template<class T, class... Args> class ConcreteSlot : public AbstractSlot<Args...>
    {
    public:
      ConcreteSlot(T *t, void(T::*f)(Args...), Signal<Args...> &s);

    private:
      ConcreteSlot(const ConcreteSlot&);
      void operator=(const ConcreteSlot&);

      friend class Signal<Args...>;

      virtual void call(Args... args){ (t->*f)(args...); }

      T *t;
      void(T::*f)(Args...);
    };

    template<class... Args> class Signal {
    private:
      std::vector<AbstractSlot<Args...>*> v;
    public:
      Signal(){ }
      ~Signal(){ for (auto i : v) i->remove(this); }

      Signal(const Signal&) = delete;
      void operator=(const Signal&) = delete;

      void connect(AbstractSlot<Args...> &s){ v.push_back(&s); s.add(this); }
      void disconnect(AbstractSlot<Args...> &s){ v.erase(std::remove(v.begin(), v.end(), &s), v.end()); }

      void emit(Args... args){ for (auto i : v) i->call(args...); }
    };

    template<class... Args> AbstractSlot<Args...>::~AbstractSlot()
    {
      for (auto i : v) i->disconnect(*this);
    }

    template<class T, class... Args> ConcreteSlot<T, Args...>::ConcreteSlot(T *t, void(T::*f)(Args...), Signal<Args...> &s) : t(t), f(f)
    {
      s.connect(*this);
    }

    class Slot {
    private:
      std::vector<BaseSlot*> v;

    public:
      Slot(void) = default;
      ~Slot(void) { for (auto i : v) delete i; }

      template<class T, class... Args> void connect(T *t, void(T::*f)(Args...), Signal<Args...> &s){ v.push_back(new ConcreteSlot<T, Args...>(t, f, s)); }

      Slot(const Slot&) = delete;
      void operator=(const Slot&) = delete;
    };
  }
}

#endif // SIP0X_UTILS_SIGNALS_HPP__
