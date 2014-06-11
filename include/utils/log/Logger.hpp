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


#define FATAL(logger, format, ...) logger->log(Sip0x::Utils::Log::Logger::FATAL, __FILE__, __LINE__, format, __VA_ARGS__)
#define ERROR(logger, format, ...) logger->log(Sip0x::Utils::Log::Logger::ERROR, __FILE__, __LINE__, format, __VA_ARGS__)
#define WARN(logger, format, ...) logger->log(Sip0x::Utils::Log::Logger::WARN, __FILE__, __LINE__, format, __VA_ARGS__)
#define INFO(logger, format, ...) logger->log(Sip0x::Utils::Log::Logger::INFO, __FILE__, __LINE__, format, __VA_ARGS__)
#define DEBUG(logger, format, ...) logger->log(Sip0x::Utils::Log::Logger::DEBUG, __FILE__, __LINE__, format, __VA_ARGS__)


namespace Sip0x
{
  namespace Utils
  {
    namespace Log
    {
      /// This parser expects a specific token and return an instance. 
      class Logger {

      public:
        enum LoggerLevel {
          FATAL = 0,
          ERROR = 1,
          WARN  = 2,
          INFO  = 3,
          DEBUG = 4
        };

      protected:
        std::string _category;
        LoggerLevel _level;
        std::ostream* _out;

      public:
        Logger(std::string const& category, std::ostream* out) {
          _category = category;
          _level = Logger::DEBUG;
          _out = out;
        }

        virtual ~Logger(void) {
        }

        void set_level(LoggerLevel level) { _level = level; }

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
        }

        static char const* conv_level_to_chars(LoggerLevel const& level) {
          if (level == Logger::DEBUG) return "DEBUG";
          if (level == Logger::INFO) return "INFO";
          if (level == Logger::WARN) return "WARN";
          if (level == Logger::ERROR) return "ERROR";
          if (level == Logger::FATAL) return "FATAL";
          return "UNKNOWN";
        }
      };
    }
  }
}


#pragma warning(pop)

#endif // SIP0X_UTILS_LOGS_LOGGER_HPP__
