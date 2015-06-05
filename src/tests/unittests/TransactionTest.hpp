#if !defined(SIP0X_TRANSACTIONTEST_HPP__)
#define SIP0X_TRANSACTIONTEST_HPP__

#include "BaseTest.hpp"

namespace unittests
{
  //! This is a set of basic unit test of Transaction classes.
  class TransactionTest : public BaseTest {
  public:
    TransactionTest();
    virtual ~TransactionTest(void);
  
    virtual void prepare(void) override;
    virtual bool execute(void) override;
  };
}

#endif // SIP0X_TRANSACTIONTEST_HPP__
