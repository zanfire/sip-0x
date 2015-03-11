#if !defined(SIP0X_UTILS_LOGS_LOGGER_HPP__)
#define SIP0X_UTILS_LOGS_LOGGER_HPP__


#pragma warning(push)
#pragma warning(disable: 4996) // Disable deprecated for MSVC.

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdarg>
#include <cstdio>


#define LOG_FATAL(logger, format, ...)  if (logger) logger->log(sip0x::Utils::Log::Logger::LOG_FATAL, __FILE__, __LINE__, format, __VA_ARGS__)
#define LOG_ERROR(logger, format, ...)  if (logger) logger->log(sip0x::Utils::Log::Logger::LOG_ERROR, __FILE__, __LINE__, format, __VA_ARGS__)
#define LOG_WARN(logger, format, ...)   if (logger) logger->log(sip0x::Utils::Log::Logger::LOG_WARN, __FILE__, __LINE__, format, __VA_ARGS__)
#define LOG_INFO(logger, format, ...)   if (logger) logger->log(sip0x::Utils::Log::Logger::LOG_INFO, __FILE__, __LINE__, format, __VA_ARGS__)
#define LOG_DEBUG(logger, format, ...)  if (logger) logger->log(sip0x::Utils::Log::Logger::LOG_DEBUG, __FILE__, __LINE__, format, __VA_ARGS__)


namespace sip0x
{
  namespace Utils
  {
    namespace Log
    {
      /// This parser expects a specific token and return an instance. 
      class Logger {

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
        Logger(std::string const& category, std::ostream* out) {
          _category = category;
          _level = Logger::LOG_WARN;
          _out = out;
        }

        virtual ~Logger(void) {
        }

        void set_level(LoggerLevel level) { _level = level; }

        LoggerLevel get_level(void) { return _level; }


        void log(LoggerLevel const& level, char const* filename, int line, char const* format, ...) {
          if (level > _level) return;

          char buffer[1024 * 2];
          char timebuf[64];

          buffer[0] = '\n';
          timebuf[0] = '\n';


          std::string time_str;
          time_t raw_time;
          struct tm * timeinfo;
          time(&raw_time);
          timeinfo = localtime(&raw_time);
          strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", timeinfo);

          int filename_len = strlen(filename);
          char const* truncated_filename = filename;
          int i = filename_len;
          while (i > 0 && (filename[i] != '/' && filename[i] != '\\')) {
            i--;
          }
          truncated_filename += i + 1;

          sprintf_s(buffer, sizeof(buffer), "%-22s|%5s|%s:%-4d|", timebuf, conv_level_to_chars(level), truncated_filename, line);
          
          *_out << buffer;
          buffer[0] = '\n';

          va_list args;
          buffer[0] = '\n';
          va_start(args, format);
          vsnprintf(buffer, sizeof(buffer), format, args);
          va_end(args);

          *_out << buffer << '\n';
          _out->flush();
        }

        static char const* conv_level_to_chars(LoggerLevel const& level) {
          if (level == Logger::LOG_DEBUG) return "DEBUG";
          if (level == Logger::LOG_INFO) return "INFO";
          if (level == Logger::LOG_WARN) return "WARN";
          if (level == Logger::LOG_ERROR) return "ERROR";
          if (level == Logger::LOG_FATAL) return "FATAL";
          return "UNKNOWN";
        }
      };
    }
  }
}


#pragma warning(pop)

#endif // SIP0X_UTILS_LOGS_LOGGER_HPP__
