#include "utils/Logger.hpp"

#include <ctime>
#include <stdio.h>

using namespace sip0x::utils;

Logger::Logger(std::string const& category, std::ostream* out) {
  _category = category;
  _level = Logger::LEVEL_WARN;
  _out = out;
}

Logger::~Logger(void) {
}

std::shared_ptr<Logger> Logger::create(std::string const& cat, std::ostream* out) {
  return std::shared_ptr<Logger>(new Logger(cat, out), Logger::deleter());
}

void Logger::log(LoggerLevel const& level, char const* filename, int line, char const* format, ...) const {
  if (level > _level) return;

  char buffer[1024 * 2];
  char timebuf[64];

  buffer[0] = '\n';
  timebuf[0] = '\n';


  std::string time_str;
  time_t raw_time;
  struct tm timeinfo;
  time(&raw_time);
  localtime_r(&raw_time, &timeinfo);
  //localtime_s(&timeinfo, &raw_time);
  strftime(timebuf, sizeof(timebuf), "%Y%m%d_%H%M%S", &timeinfo);

  int filename_len = strlen(filename);
  char const* truncated_filename = filename;
  int i = filename_len;
  while (i > 0 && (filename[i] != '/' && filename[i] != '\\')) {
    i--;
  }
  truncated_filename += i + 1;

  //sprintf_s(buffer, sizeof(buffer), "%-16s|%s|%s:%-4d|", timebuf, conv_level_to_chars(level), truncated_filename, line);
  std::sprintf(buffer, "%-16s|%s|%s:%-4d|", timebuf, conv_level_to_chars(level), truncated_filename, line);
          
  *_out << buffer;
  buffer[0] = '\n';

  va_list args;
  buffer[0] = '\n';
  va_start(args, format);
  std::vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  *_out << buffer << '\n';
  _out->flush();
}

char const* Logger::conv_level_to_chars(LoggerLevel const& level) {
  if (level == Logger::LEVEL_DEBUG) return "D";
  if (level == Logger::LEVEL_INFO)  return "I";
  if (level == Logger::LEVEL_WARN)  return "W";
  if (level == Logger::LEVEL_ERROR) return "E";
  if (level == Logger::LEVEL_FATAL) return "F";
  return "U";
}
