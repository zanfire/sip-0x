#include <iostream>

// asio test
//#define _WIN32_WINNT 0x0501
//#define ASIO_STANDALONE
//#include <asio.hpp>

#include "parser/SIPGrammar.hpp"

#include "parser/private/TokenRegex.hpp"
#include "parser/private/OpAlternative.hpp"
#include "parser/private/OpOccurrence.hpp"

#include "parser/Parser.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"
#include "utils/IniFile.hpp"

using namespace Sip0x::Parser;
using namespace Sip0x::Utils;
using namespace Sip0x::Utils::Log;
using namespace std;


// Prototypes
void test_occurrences();

int main(int argc, char const* argv[]) {
  std::string str;
  LoggerManager* loggermanager = LoggerManager::get_instance();
  loggermanager->configure("..\\docs\\logger.ini");
  
  test_occurrences();
  
  getline(std::cin, str);
  return 0;
}