#include <iostream>

#include "test_prototypes.h"
#include "utils/LoggerFactory.hpp"

#include "unittests/TestExecutor.hpp"
#include "unittests/SIPParserTest.hpp"
#include "unittests/SIPParserFromFileTest.hpp"


using namespace sip0x::utils;
using namespace std;


int main(int argc, char const* argv[]) {
  LoggerFactory* loggermanager = LoggerFactory::get_instance();
  loggermanager->configure("..\\docs\\logger.ini");

  cout << "sip-0x library tests..." << endl;

  unittests::TestExecutor executor;
  executor.add(std::make_shared<unittests::SIPParserTest>());
  executor.add(std::make_shared<unittests::SIPParserFromFileTest>("..\\tests\\sip_requests.txt"));
  executor.add(std::make_shared<unittests::SIPParserFromFileTest>("..\\tests\\sip_responses.txt"));

  executor.process();

  //test_sipmessages_from_file("..\\tests\\sip_requests.txt", true);
  //test_sipmessages_from_file("..\\tests\\sip_responses.txt", false);
 
  test_token_sip_message();
  test_token_sipuri();
  test_token_regexconststrings();
  test_token_ipv4();
  test_occurrences();

  cout << "Tests finished.";
  std::string str;
  getline(std::cin, str);
  return 0;
}