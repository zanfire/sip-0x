#include "LoggerFactory.hpp"

#include "IniFile.hpp"

#include <mutex>

using namespace sip0x::utils;

std::once_flag*  LoggerFactory::_once = new std::once_flag();
LoggerFactory*	LoggerFactory::_instance = nullptr;


LoggerFactory::LoggerFactory(void) {
  _mtx = new std::recursive_mutex();
}

LoggerFactory::~LoggerFactory(void) {
  delete _mtx;
}

std::shared_ptr<Logger> LoggerFactory::get_logger(char const* n) {
  std::string name(n);

  LoggerFactory* manager = get_instance();

  std::lock_guard<std::recursive_mutex> lock(*manager->_mtx);
  std::size_t pos = std::string::npos;
  // Search on sub-token
  do {
    // NOTE: Using count method to avoid the creation that happen with the operator[].
    if (manager->_loggers.count(name) > 0) {
      return manager->_loggers[name];
    }
    pos = name.find_last_of('.');
    if (pos != std::string::npos) {
      name = name.substr(0, pos);
    }
  } while (pos != std::string::npos);


  // Load configuration details, using the given name (n) instead of modified name.
  std::shared_ptr<Logger> logger = Logger::create(n, &std::cout);
  logger->set_level(manager->_default_level);
  manager->_loggers[n] = logger;
  return logger;
}

//! Get singleton instance of LoggerFactory.
LoggerFactory* LoggerFactory::get_instance(void) {
  std::call_once(*LoggerFactory::_once,
    []()
  {
    LoggerFactory::_instance = new LoggerFactory();
  });

  return LoggerFactory::_instance;
}


// Load configuration from a INI file.
bool LoggerFactory::configure(std::string path) {
  std::lock_guard<std::recursive_mutex> lock(*_mtx);

  std::unique_ptr<IniFile> ini = IniFile::open(path);
  if (ini != nullptr) {
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
        current = Logger::create(entry.first, out);
      }

      current->set_level(level);

      _loggers[entry.first] = current;
    }
  }
  else {
    std::cout << "Failed to open file " << path << std::endl;
  }
  ini.release();
  return false;
}


void LoggerFactory::parse_logger_configuration(std::string cfg, std::string& level, std::ostream** output) {
  int idx = cfg.find_first_of(',');
  if (idx > 0) {
    level = trim(cfg.substr(0, idx));
    std::string output_id = trim(cfg.substr(idx + 1));
    *output = _outputs[output_id];
  }
  else {
    level = cfg;
  }
}


std::ostream* LoggerFactory::parse_output_configuration(std::string cfg) {
  if (cfg.compare("Console") == 0) {
    return &std::cout;
  }
  else {
    // Split
    int idx = cfg.find_first_of(',');
    if (idx > 0) {
      std::string path = trim(cfg.substr(idx + 1));
      std::ofstream* ofs = new std::ofstream();
      ofs->open(path, std::ofstream::out | std::ofstream::app);

      ofs->flush();
      return ofs;
    }
  }
  return &std::cout;
}


Logger::LoggerLevel LoggerFactory::conv_logger_level_from_string(std::string level) {
  if (level.compare("FATAL") == 0) return Logger::LEVEL_FATAL;
  if (level.compare("ERROR") == 0) return Logger::LEVEL_ERROR;
  if (level.compare("WARN") == 0) return  Logger::LEVEL_WARN;
  if (level.compare("INFO") == 0) return  Logger::LEVEL_INFO;
  if (level.compare("DEBUG") == 0) return Logger::LEVEL_DEBUG;
  return Logger::LEVEL_DEBUG;
}