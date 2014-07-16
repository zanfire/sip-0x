#if !defined(SIP0X_UTILS_STREAMINPUT_HPP__)
#define SIP0X_UTILS_STREAMINPUT_HPP__

#include <string>

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"

namespace Sip0x
{
  namespace Utils
  {
    using namespace Sip0x::Utils::Log;

    // Helper class that handle a string as a seekable stream.
    // This class is not thread safe.
    class InputTokenStream {

    protected:
      std::shared_ptr<Logger> _logger;
      std::string _content;
      int _pos;


    public:
      InputTokenStream(std::string& str) {
        _logger = LoggerManager::get_logger("Sip0x.Utils.InputTokenStream");
        _content = str;
        _pos = 0;
      }

      virtual ~InputTokenStream(void) {
      }

      // Returns the current position in the content.
      int pos(void) { return _pos; }

      // Returns the number of chars available to get.
      int remains(void) { return _content.length() - _pos; }
      
      char get_char(void) {
        if (_pos + 1 > (int)_content.length()) {
          return -1;
        }
        return _content.at(_pos++);
      }

      std::string str(void) {
        return _content;
      }

      std::string str(int pos, int chars) {
        return _content.substr(pos, chars);;
      }

      std::string get(void) {
        return get(remains());
      }

      std::string get(int chars) {
        std::string str = _content.substr(_pos, chars);
        _pos += str.length();
        return str;
      }

      std::string unget(int chars) {
        _pos -= chars;
      }

      void seekg(int pos) {
        _pos = pos;
      }

      bool eof(void) {
        return _pos >= (int)_content.length();
      }
    };
  }
}

#endif // SIP0X_UTILS_INIFILE_HPP__
