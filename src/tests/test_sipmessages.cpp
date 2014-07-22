#include "test_prototypes.h"

#include "parser/sip/TokenSIPMessage.hpp"

#include <fstream>


using namespace Sip0x::Parser;
using namespace Sip0x::Utils;
using namespace Sip0x::Utils::Log;
using namespace std;

void test_sipmessages_from_file(char const* path) {
  std::shared_ptr<Logger> logger = LoggerManager::get_logger("Test.sipmessages");

  TokenSIPMessage sip;

  cout << "parser size: " << sizeof(sip) << endl;

  std::ifstream ifs(path, std::ifstream::in);
  if (!ifs.is_open()) {
    ERROR(logger, "Failed to open INI file [%s].", path);
    return;
  }

  char const* begin_marker = "--BEGIN--";
  char const* end_marker = "--END--";
  
  std::string line;
  std::string content;

  bool reading_content = false;
  while (ifs.good()) {
    std::getline(ifs, line);

    if (!reading_content && line.compare(begin_marker) == 0) {
      content = "";
      reading_content = true;
    }
    else if (reading_content && line.compare(end_marker) == 0) {
      run_test(sip, content, true, true);
      reading_content = false;
    }
    else if (reading_content) {
      content += line + "\r\n";
    }
  }
}