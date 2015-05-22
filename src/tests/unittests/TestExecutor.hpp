#if !defined(SIP0X_TESTEXECUTOR_HPP__)
#define SIP0X_TESTEXECUTOR_HPP__

#include <string>
#include <vector>
#include <memory>

namespace unittests
{
  class BaseTest;

  //! Execute a set of test.
  class TestExecutor {
  protected:
    //! Collection of tests.
    std::vector<std::shared_ptr<unittests::BaseTest>> _tests;
    //!
    bool _stop_at_first_failure = true;
  public:
    TestExecutor(void);
    virtual ~TestExecutor(void);

    //! Add a test to the executor.
    void add(std::shared_ptr<unittests::BaseTest> test);

    //! Run the test cases.
    bool process(void);
  };
}

#endif // SIP0X_TESTEXECUTOR_HPP__
