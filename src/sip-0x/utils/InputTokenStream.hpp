#if !defined(SIP0X_UTILS_STREAMINPUT_HPP__)
#define SIP0X_UTILS_STREAMINPUT_HPP__

#include <string>

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

namespace sip0x
{
  namespace Utils
  {
    using namespace sip0x::Utils;

    // Helper class that handle a string as a seekable stream.
    // This class is not thread safe.
    class InputTokenStream {

    protected:
      std::shared_ptr<Logger> _logger;
      std::string _content;
      std::size_t const _size;
      unsigned long _pos = 0;


    public:
      InputTokenStream(std::string& str) : _content(str), _size(str.length()) {
        _logger = LoggerFactory::get_logger("sip0x.Utils.InputTokenStream");
      }

      InputTokenStream(uint8_t const* content, std::size_t const& size) : _content((const char*)content, size), _size(size) {
        _logger = LoggerFactory::get_logger("sip0x.Utils.InputTokenStream");
      }

      virtual ~InputTokenStream(void) {
      }

      // Delete copy constructor.
      InputTokenStream& operator=(InputTokenStream const&) = delete;
      InputTokenStream(InputTokenStream const&) = delete;

      // Returns the current position in the content.
      int pos(void) { return _pos; }

      // Returns the number of chars available to get.
      int remains(void) { return _size - _pos; }
      
      char get_char(void) {
        if (_pos + 1 > _size) {
          return -1;
        }
        return _content[_pos++];
      }

      std::string str(void) {
        return _content;
      }

      std::string str(int pos, int chars) {
        return std::string((char const*)(_content.c_str() + pos), chars);
      }

      std::string get(void) {
        return get(remains());
      }

      std::string get(int chars) {
        std::string s = str(_pos, chars);
        _pos += s.length();
        return s;
      }

      char const* get_cstr(void) {
        return (char const*)(_content.c_str() + _pos);
      }

      std::string unget(int chars) {
        _pos -= chars;
      }

      void seekg(int pos) {
        _pos = pos;
      }

      bool eof(void) {
        return _pos >= _size;
      }
    };
  }
}

#endif // SIP0X_UTILS_INIFILE_HPP__
