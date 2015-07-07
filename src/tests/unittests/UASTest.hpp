#if !defined(SIP0X_UASTEST_HPP__)
#define SIP0X_UASTEST_HPP__

#include "BaseTest.hpp"

#include "../mocks/TransportLayerMock.hpp"

namespace unittests
{
  //! This is a set of basic unit test of Transaction classes.
  class UASTest : public BaseTest {
  protected:
    std::shared_ptr<mocks::TransportLayerMock> _transport;
    
  public:
    UASTest(void);
    virtual ~UASTest(void);
  
    virtual void prepare(void) override;
    virtual bool execute(void) override;
  };
}

#endif // SIP0X_UASTEST_HPP__
