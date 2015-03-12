#if !defined(SIP0X_UTILS_INIFILE_HPP__)
#define SIP0X_UTILS_INIFILE_HPP__

#include <memory>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>

#include <cctype>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <regex>

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

namespace sip0x
{
  namespace Utils
  {
    using namespace sip0x::Utils;

    // Wrapper over an INI file.
    class IniFile {

    protected:
      std::shared_ptr<Logger> _logger;
      std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _sections;

    protected:
      IniFile(void) {
        _logger = LoggerFactory::get_logger("sip0x.Utils.IniFile");
      }

    public:
      virtual ~IniFile(void) {
      }

      static std::unique_ptr<IniFile> open(std::string path) {
        std::unique_ptr<IniFile> ini;
        ini.reset(new IniFile());

        std::ifstream ifs(path.c_str(), std::ifstream::in);
        if (!ifs.is_open()) {
          LOG_ERROR(ini->_logger, "Failed to open INI file [%s].", path.c_str());
          ini.release();
          ini.reset();
          return ini;
        }

        std::regex section_regex("\\[.*\\]");
        std::regex entry_regex(".*=.*");
        
        std::string line;
        std::string cur_section = "[DEFAULT]";
        std::unordered_map<std::string, std::string> cur_entries;

        while (ifs.good()) {
          std::getline(ifs, line);

          line = trim(line);

          // Add section.
          if (line[0] == '#') {
            LOG_DEBUG(ini->_logger, "Skipping comment: \"%s\".", line.c_str());
          }
          else if (std::regex_match(line, section_regex)) {
            LOG_DEBUG(ini->_logger, "Adding section \"%s\".", line.c_str());

            // Add current entires.
            if (cur_entries.size() > 0) {
              // Copy ...
              ini->_sections[cur_section] = cur_entries;
              cur_entries.clear();
            }

            cur_section = line.substr(1, line.length() - 2);

          }
          else if (std::regex_match(line, entry_regex)) {
            // Add entry per section.

            unsigned found = line.find_first_of('=');
            std::string key = trim(line.substr(0, found));
            std::string value = trim(line.substr(found + 1));

            cur_entries[key] = value;

            LOG_DEBUG(ini->_logger, "Adding entry \"%s\", key %s value %s.", line.c_str(), key.c_str(), value.c_str());
          }
          else if (line.empty()) {
            // nop ...
          }
          else {
            LOG_WARN(ini->_logger, "Line \"%s\" wasn't recognized. Skipping line.", line.c_str());
          }

          line.clear();
        }

        if (cur_entries.size() > 0) {
          // Copy ...
          ini->_sections[cur_section] = cur_entries;
        }

        ifs.close();

        return ini;
      }

      static std::string trim(const std::string &s) {
        auto  wsfront = std::find_if_not(s.begin(), s.end(), std::isspace);
        return std::string(wsfront, std::find_if_not(s.rbegin(), std::string::const_reverse_iterator(wsfront), [](int c){return std::isspace(c); }).base());
      }


      // Query for a value in the ini file.
      std::string entry(std::string section, std::string key, std::string default = "") {
        std::unordered_map<std::string, std::string> sec = _sections[section];

        std::unordered_map<std::string, std::string>::const_iterator got = sec.find(key);

        if (got == sec.cend()) {
          return default;
        }
        else {
          return got->second;
        }
      }

      std::unordered_map<std::string, std::string> section(std::string section) {
        return _sections[section];
      }

      void dump(std::ostream& out) {
        for (auto section : _sections) {
          out << '[' << section.first << ']' << std::endl;
          for (auto entry : section.second) {
            out << entry.first << " = "<< entry.second << std::endl;
          }
        }
      }
    };
  }
}

#endif // SIP0X_UTILS_INIFILE_HPP__
