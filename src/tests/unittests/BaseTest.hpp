#if !defined(SIP0X_BASETEST_HPP__)
#define SIP0X_BASETEST_HPP__

#include <string>

namespace unittests
{
  //! Model unit test interface.
  class BaseTest {
  protected:
    std::string _name;
    std::string _description;
  
    BaseTest(std::string const& name, std::string const& desc);
    virtual ~BaseTest(void);
  
  public:
    std::string name(void) { return _name; }
    std::string description(void) { return _description; }

    virtual void prepare(void) {}
    virtual bool execute(void) = 0;
    virtual void cleanup(void) {}
  };
}

#endif // SIP0X_BASETEST_HPP__
