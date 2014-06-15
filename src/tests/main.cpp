#include <iostream>

#include "test_prototypes.h"

#include "utils/log/LoggerManager.hpp"

using namespace Sip0x::Utils::Log;
using namespace std;


int main(int argc, char const* argv[]) {
  std::string str;
  LoggerManager* loggermanager = LoggerManager::get_instance();
  loggermanager->configure("..\\docs\\logger.ini");
  
  test_token_sipuri();
  //test_token_ipv4();
  //test_occurrences();
  
  getline(std::cin, str);
  return 0;
}