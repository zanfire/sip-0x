#include "utils/utils.hpp"

#include <string>

namespace sip0x
{
  namespace utils
  {
    std::string trim(const std::string& input) {
      int start = 0;
      int end = input.size();
      for (auto& c : input) {
        if (std::isspace(c)) start++;
        else break;
      }
      for (auto i = input.rbegin(); i != input.rend(); ++i) {
        if (std::isspace(*i)) end--;
        else break;
      }
      return std::string(start, end - start);
    }
  }
}

#
