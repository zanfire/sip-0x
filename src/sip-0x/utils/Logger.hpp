#if !defined(SIP0X_UTILS_LOGGER_HPP__)
#define SIP0X_UTILS_LOGGER_HPP__

#pragma warning(push)
#pragma warning(disable: 4996) // Disable deprecated for MSVC.

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdarg>
#include <cstdio>

//! Use define to provide more information to the logger facility.
#define LOG_FATAL(logger, format, ...)  if (logger) logger->log(sip0x::Utils::Logger::LOG_FATAL, __FILE__, __LINE__, format, __VA_ARGS__)
#define LOG_ERROR(logger, format, ...)  if (logger) logger->log(sip0x::Utils::Logger::LOG_ERROR, __FILE__, __LINE__, format, __VA_ARGS__)
#define LOG_WARN(logger, format, ...)   if (logger) logger->log(sip0x::Utils::Logger::LOG_WARN, __FILE__, __LINE__, format, __VA_ARGS__)
#define LOG_INFO(logger, format, ...)   if (logger) logger->log(sip0x::Utils::Logger::LOG_INFO, __FILE__, __LINE__, format, __VA_ARGS__)
#define LOG_DEBUG(logger, format, ...)  if (logger) logger->log(sip0x::Utils::Logger::LOG_DEBUG, __FILE__, __LINE__, format, __VA_ARGS__)


namespace sip0x
{
  namespace Utils
  {
    
    //! Logger facility
    //!
    //! Provide a logger facility for logging.
    class Logger {
      class deleter;
      friend class LoggerFactory;
      friend class deleter;
    private:
      
      class deleter {
      public:
        void operator()(Logger* ptr) { delete ptr; }
      };

    public:
      enum LoggerLevel {
        LOG_FATAL = 0,
        LOG_ERROR = 1,
        LOG_WARN  = 2,
        LOG_INFO = 3,
        LOG_DEBUG = 4
      };

    protected:
      std::string _category;
      LoggerLevel _level;
      std::ostream* _out;

    public:
      // Level setter and getter
      void set_level(LoggerLevel level) { _level = level; }
      LoggerLevel get_level(void) { return _level; }

      //! Log a line to the appender.
      void log(LoggerLevel const& level, char const* filename, int line, char const* format, ...);

      //! Returns a string  of LoggerLevel.
      static char const* conv_level_to_chars(LoggerLevel const& level);

    protected:
      //! Logger is created via the get_logger method of LoggerFactory.
      Logger(std::string const& category, std::ostream* out);
      virtual ~Logger(void);

      static std::shared_ptr<Logger> create(std::string const& cat, std::ostream* out);
    };
  }
}


#pragma warning(pop)

#endif // SIP0X_UTILS_LOGGER_HPP__
