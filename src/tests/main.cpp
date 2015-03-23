#include <iostream>

#include "test_prototypes.h"

#include "utils/LoggerFactory.hpp"


using namespace sip0x::utils;
using namespace std;


int main(int argc, char const* argv[]) {
  LoggerFactory* loggermanager = LoggerFactory::get_instance();
  loggermanager->configure("..\\docs\\logger.ini");

  cout << "sip-0x library tests..." << endl;

  //test_sipmessages_from_file("..\\tests\\sip_requests.txt");
  //test_sipmessages_from_file("..\\tests\\sip_responses.txt");
 
  test_token_sip_message();
  test_token_sipuri();
  test_token_regexconststrings();
  test_token_ipv4();
  test_occurrences();
  std::string str;
  getline(std::cin, str);
  return 0;
}