#include <utils/log/LoggerManager.hpp>

#include <utils/IniFile.hpp>

#include <mutex>

using namespace sip0x::Utils::Log;

std::once_flag*  LoggerManager::_once = new std::once_flag();
LoggerManager*	LoggerManager::_instance = nullptr;


LoggerManager::LoggerManager(void) {
  _mtx = new std::recursive_mutex();
}

LoggerManager::~LoggerManager(void) {
  delete _mtx;
}

std::shared_ptr<Logger> LoggerManager::get_logger(char const* name) {
  LoggerManager* manager = get_instance();

  std::lock_guard<std::recursive_mutex> lock(*manager->_mtx);

  std::shared_ptr<Logger> logger = manager->_loggers[name];
  if (!logger) {
    // Load configuration details 
    logger.reset(new Logger(name, &std::cout));
    logger->set_level(manager->_default_level);

    manager->_loggers[name] = logger;
  }

  return logger;
}

//! Get singleton instance of LoggerManager.
LoggerManager* LoggerManager::get_instance(void) {
  std::call_once(*LoggerManager::_once,
    []()
  {
    LoggerManager::_instance = new LoggerManager();
  });

  return LoggerManager::_instance;
}


// Load configuration from a INI file.
bool LoggerManager::configure(std::string path) {
  std::lock_guard<std::recursive_mutex> lock(*_mtx);

  std::unique_ptr<IniFile> ini = IniFile::open(path);
  if (ini) {
    // 1. Parse output, thay are needed by the logging.
    // Reconfigure all logger and pre-create described logger.
    {
      std::unordered_map<std::string, std::string> entries = ini->section("OUTPUT");
      for (auto entry : entries) {
        std::ostream* current = _outputs[entry.first];
        
        if (current == nullptr) {
          current =  parse_output_configuration(entry.second);
        }
    
        _outputs[entry.first] = current;
      }
    }



    // Reconfigure all logger and pre-create described logger.
    std::unordered_map<std::string, std::string> entries = ini->section("LOGGING");


    // Set default.
    _default_level = conv_logger_level_from_string(ini->entry("LOGGING", "default", "LOG_WARN"));
    for (auto logger : _loggers) {
      logger.second->set_level(_default_level);
    }

    // Pre-create entry and configure existing.
    for (auto entry : entries) {
      std::shared_ptr<Logger> current = _loggers[entry.first];
      std::string lv;
      std::ostream* out = nullptr;
      parse_logger_configuration(entry.second, lv, &out);
      Logger::LoggerLevel level = conv_logger_level_from_string(lv);

      if (out == nullptr) {
        out = &std::cout;
      }
      if (!current) {
        current.reset(new Logger(entry.first, out));
      }

      current->set_level(level);

      _loggers[entry.first] = current;
    }
  }
  ini.release();
  return false;
}