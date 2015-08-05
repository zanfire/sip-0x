#if !defined(SIP0X_UTILS_LOGGER_HPP__)
#define SIP0X_UTILS_LOGGER_HPP__

// Add MS VC guard
//#pragma warning(push)
//#pragma warning(disable: 4996) // Disable deprecated for MSVC.

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdarg>
#include <cstdio>

//! Use define to provide more information to the logger facility.
//! /remark The check against the level is performed before logger to avoid evaluate variant.
#define LOG_FATAL_STR(logger, format)  if (logger && logger->get_level() >= sip0x::utils::Logger::LEVEL_FATAL) logger->log(sip0x::utils::Logger::LEVEL_FATAL, __FILE__, __LINE__, "%s", format)
#define LOG_ERROR_STR(logger, format)  if (logger && logger->get_level() >= sip0x::utils::Logger::LEVEL_ERROR) logger->log(sip0x::utils::Logger::LEVEL_ERROR, __FILE__, __LINE__, "%s", format)
#define LOG_WARN_STR(logger, format)   if (logger && logger->get_level() >= sip0x::utils::Logger::LEVEL_WARN) logger->log(sip0x::utils::Logger::LEVEL_WARN, __FILE__, __LINE__,   "%s", format)
#define LOG_INFO_STR(logger, format)   if (logger && logger->get_level() >= sip0x::utils::Logger::LEVEL_INFO) logger->log(sip0x::utils::Logger::LEVEL_INFO, __FILE__, __LINE__,   "%s", format)
#define LOG_DEBUG_STR(logger, format)  if (logger && logger->get_level() >= sip0x::utils::Logger::LEVEL_DEBUG) logger->log(sip0x::utils::Logger::LEVEL_DEBUG, __FILE__, __LINE__, "%s", format)

#define LOG_FATAL(logger, ...)  if (logger && logger->get_level() >= sip0x::utils::Logger::LEVEL_FATAL) logger->log(sip0x::utils::Logger::LEVEL_FATAL, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(logger, ...)  if (logger && logger->get_level() >= sip0x::utils::Logger::LEVEL_ERROR) logger->log(sip0x::utils::Logger::LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(logger, ...)   if (logger && logger->get_level() >= sip0x::utils::Logger::LEVEL_WARN) logger->log(sip0x::utils::Logger::LEVEL_WARN, __FILE__, __LINE__,  __VA_ARGS__)
#define LOG_INFO(logger, ...)   if (logger && logger->get_level() >= sip0x::utils::Logger::LEVEL_INFO) logger->log(sip0x::utils::Logger::LEVEL_INFO, __FILE__, __LINE__,  __VA_ARGS__)
#define LOG_DEBUG(logger, ...)  if (logger && logger->get_level() >= sip0x::utils::Logger::LEVEL_DEBUG) logger->log(sip0x::utils::Logger::LEVEL_DEBUG, __FILE__, __LINE__,  __VA_ARGS__)


namespace sip0x
{
  namespace utils
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
        LEVEL_FATAL = 0,
        LEVEL_ERROR = 1,
        LEVEL_WARN  = 2,
        LEVEL_INFO = 3,
        LEVEL_DEBUG = 4
      };

    protected:
      std::string _category;
      LoggerLevel _level;
      std::ostream* _out;

    public:
      // Level setter and getter
      void set_level(LoggerLevel level) { _level = level; }
      LoggerLevel get_level(void) const { return _level; }

      //! Log a line to the appender.
      void log(LoggerLevel const& level, char const* filename, int line, char const* format, ...) const;

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


//#pragma warning(pop)

#endif // SIP0X_UTILS_LOGGER_HPP__
