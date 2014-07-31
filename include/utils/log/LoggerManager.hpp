#if !defined(SIP0X_UTILS_LOGS_LOGGERMANAGER_HPP__)
#define SIP0X_UTILS_LOGS_LOGGERMANAGER_HPP__

#include <memory>
#include <unordered_map>
#include <mutex>
#include <iostream>

#include <utils/log/Logger.hpp>


namespace Sip0x
{
  namespace Utils
  {
    namespace Log
    {
      // 
      class LoggerManager {

      protected:
        static LoggerManager* _instance;
        static std::once_flag _once;

        std::recursive_mutex _mtx;
        std::unordered_map<std::string, std::shared_ptr<Logger>> _loggers;

        // Default values.
        Logger::LoggerLevel _default_level;

      public:
        static std::shared_ptr<Logger> get_logger(char const* name) {
          LoggerManager* manager = get_instance();

          std::lock_guard<std::recursive_mutex> lock(manager->_mtx);

          std::shared_ptr<Logger> logger = manager->_loggers[name];
          if (!logger) {
            // Load configuration details 
            logger.reset(new Logger(name, &std::cout));
            logger->set_level(manager->_default_level);

            manager->_loggers[name] = logger;
          }

          return logger;
        }

        static LoggerManager* get_instance(void) {
          std::call_once(LoggerManager::_once,
            []()
          {
            LoggerManager::_instance = new LoggerManager();
          });

          return LoggerManager::_instance;
        }

        // Load configuration from a INI file.
        bool configure(std::string path);
        
        static Logger::LoggerLevel conv_logger_level_from_string(std::string level) {
          if (level.compare("FATAL") == 0) return Logger::FATAL;
          if (level.compare("LOG_ERROR") == 0) return Logger::LOG_ERROR;
          if (level.compare("LOG_WARN") == 0) return Logger::LOG_WARN;
          if (level.compare("INFO") == 0) return Logger::INFO;
          if (level.compare("LOG_DEBUG") == 0) return Logger::LOG_DEBUG;
          return Logger::LOG_DEBUG;
        }
      protected:
        LoggerManager(void) {
          _default_level = Logger::LOG_DEBUG;
        }

      public:
        virtual ~LoggerManager(void) {}
      };
    }
  }
}

#endif // SIP0X_UTILS_LOGS_LOGGERMANAGER_HPP__
