#include "TestExecutor.hpp"

#include "BaseTest.hpp"

#include <iostream>

using namespace unittests;

TestExecutor::TestExecutor(void) {
}


TestExecutor::~TestExecutor(void) {
}

void TestExecutor::add(std::shared_ptr<unittests::BaseTest> test) {
  _tests.push_back(test);
}

bool TestExecutor::process(void) {
  bool result = true;
  for (auto t : _tests) {
    std::cout << "Running " << t->name() << " test: ";

    t->prepare();
    bool r = t->execute();
    t->cleanup();

    std::cout << r ? "OK" : "FAILED";
    result &= r;
    if (!result &&_stop_at_first_failure) {
      break;
    }
  }
  return result;
}

