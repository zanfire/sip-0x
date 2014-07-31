#include <utils/log/LoggerManager.hpp>

#include <utils/IniFile.hpp>

using namespace Sip0x::Utils::Log;

std::once_flag  LoggerManager::_once;
LoggerManager*	LoggerManager::_instance = nullptr;


bool LoggerManager::configure(std::string path) {
  std::lock_guard<std::recursive_mutex> lock(_mtx);

  std::unique_ptr<IniFile> ini = IniFile::open(path);
  if (ini) {
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
      Logger::LoggerLevel level = conv_logger_level_from_string(entry.second);

      if (!current) {
        current.reset(new Logger(entry.first, &std::cout));
      }

      current->set_level(level);

      _loggers[entry.first] = current;
    }
  }
  ini.release();
  return false;
}
 