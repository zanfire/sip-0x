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

        std::mutex _mtx;
        std::unordered_map<std::string, std::shared_ptr<Logger>> _loggers;

      public:
        static std::shared_ptr<Logger> get_logger(char const* name) {
          LoggerManager* manager = get_instance();

          std::lock_guard<std::mutex> lock(manager->_mtx);

          std::shared_ptr<Logger> logger = manager->_loggers[name];
          if (!logger) {
            // Load configuration details 
            logger.reset(new Logger(name, &std::cout));
            logger->set_level(Logger::DEBUG);

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

        bool configure(std::string path) {
          std::lock_guard<std::mutex> lock(_mtx);

          // Destroy reconfigure all logger and pre-create described logger.
          return false;
        }
        
      protected:
        LoggerManager(void) {}
      public:
        virtual ~LoggerManager(void) {}
      };
    

      // No good!!!
      std::once_flag  LoggerManager::_once;
      LoggerManager*	LoggerManager::_instance = nullptr;
    }
  }
}

#endif // SIP0X_UTILS_LOGS_LOGGER_HPP__
