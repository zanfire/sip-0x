#if !defined(SIP0X_SIPPARSERTEST_HPP__)
#define SIP0X_SIPPARSERTEST_HPP__

#include "BaseTest.hpp"

namespace unittests
{
  //! Model unit test interface.
  class SIPParserTest : BaseTest {
  protected:
    SIPParserTest();
    virtual ~SIPParserTest(void);
  
  public:
    virtual void prepare(void) override;
    virtual bool execute(void) override;
  };
}

#endif // SIP0X_SIPPARSERTEST_HPP__
