#if !defined(SIP0X_UTILS_LOGS_LOGGER_HPP__)
#define SIP0X_UTILS_LOGS_LOGGER_HPP__

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdarg>
#include <cstdio>


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
        LoggerLevel _level;
        std::ostream* _out;

      public:
        Logger(std::ostream* out) {
          _level = Logger::DEBUG;
          _out = out;
        }

        virtual ~Logger(void) {
        }

        void set_level(LoggerLevel level) { _level = level; }

        void log(LoggerLevel const& level, char const* filename, int line, char const* format, ...) {
          if (level > _level) return;

          char buffer[1024 * 4];
          buffer[0] = '\n';

          std::string time_str;
          time_t raw_time;
          struct tm * timeinfo;
          time(&raw_time);
          timeinfo = localtime(&raw_time);
          strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
          
          *_out << buffer << "|";


          va_list args;
          buffer[0] = '\n';
          va_start(args, format);
          vsnprintf(buffer, sizeof(buffer), format, args);
          va_end(args);

          *_out << buffer << '\n';
        }

      protected:

        std::string timestamps(void) {

        }
      };
    }
  }
}

#define LOGE(logger, format, ...) logger->log(Sip0x::Utils::Log::Logger::ERROR, __FILE__, __LINE__, format, __VA_ARGS__)

#endif // SIP0X_UTILS_LOGS_LOGGER_HPP__
