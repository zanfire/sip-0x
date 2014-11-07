#if !defined(SIP0X_UTILS_LOGS_LOGGERMANAGER_HPP__)
#define SIP0X_UTILS_LOGS_LOGGERMANAGER_HPP__

#include <memory>
#include <unordered_map>
#ifdef _M_CEE
namespace std {
  struct once_flag;
  class recursive_mutex;
}
#else
# include <mutex>
#endif
#include <fstream>
#include <cctype>
#include <algorithm>

#include <utils/log/Logger.hpp>

namespace sip0x
{
  namespace Utils
  {
    namespace Log
    {
      // 
      class LoggerManager {

      protected:
        static LoggerManager* _instance;
        static std::once_flag* _once;
        std::recursive_mutex* _mtx;

        std::unordered_map<std::string, std::ostream*> _outputs;
        std::unordered_map<std::string, std::shared_ptr<Logger>> _loggers;


        // Default values.
        Logger::LoggerLevel _default_level = Logger::LOG_DEBUG;

      public:
        static std::shared_ptr<Logger> get_logger(char const* name);
        //! Get singleton instance of LoggerManager.
        static LoggerManager* get_instance(void);
        
        bool configure(std::string path);

        
        //! \brief Convert level to enum value.
        static Logger::LoggerLevel conv_logger_level_from_string(std::string level) {
          if (level.compare("FATAL") == 0) return Logger::LOG_FATAL;
          if (level.compare("ERROR") == 0) return Logger::LOG_ERROR;
          if (level.compare("WARN") == 0) return Logger::LOG_WARN;
          if (level.compare("INFO") == 0) return Logger::LOG_INFO;
          if (level.compare("DEBUG") == 0) return Logger::LOG_DEBUG;
          return Logger::LOG_DEBUG;
        }

        //! \brief Parse logger entry.
        void parse_logger_configuration(std::string cfg, std::string& level, std::ostream** output) {
          int idx = cfg.find_first_of(',');
          if (idx > 0) {
            level = trim(cfg.substr(0, idx));
            std::string output_id  = trim(cfg.substr(idx + 1));
            *output = _outputs[output_id];
          }
          else {
            level = cfg;
          }
        }

        std::ostream* parse_output_configuration(std::string cfg) {
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


      protected:
        LoggerManager(void);

        static std::string trim(const std::string &s) {
          auto  wsfront = std::find_if_not(s.begin(), s.end(), std::isspace);
          return std::string(wsfront, std::find_if_not(s.rbegin(), std::string::const_reverse_iterator(wsfront), [](int c){return std::isspace(c); }).base());
        }

      public:
        virtual ~LoggerManager(void);
      };
    }
  }
}

#endif // SIP0X_UTILS_LOGS_LOGGERMANAGER_HPP__
