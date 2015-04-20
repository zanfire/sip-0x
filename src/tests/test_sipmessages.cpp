#include "test_prototypes.h"

#include "parser/tokens/TokenSIPMessage.hpp"

#include <fstream>


using namespace sip0x::parser;
using namespace sip0x::utils;

using namespace std;

void test_sipmessages_from_file(char const* path, bool break_on_error) {
  std::shared_ptr<Logger> logger = LoggerFactory::get_logger("Test.sipmessages");

  std::ifstream ifs(path, std::ifstream::in);
  if (!ifs.is_open()) {
    LOG_ERROR(logger, "Failed to open INI file [%s].", path);
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
      bool result = run_sip(content);
      if (break_on_error && !result) {
        break;
      }
      reading_content = false;
    }
    else if (reading_content) {
      content += line + "\r\n";
    }
  }
}