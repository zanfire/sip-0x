#if !defined(SIP0X_UTILS_LOGGERMANAGER_HPP__)
#define SIP0X_UTILS_LOGGERMANAGER_HPP__

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

#include <utils/Logger.hpp>

namespace sip0x
{
  namespace utils
  {
    //! Create or re-use a Logger instances.
    //!
    //! Create or re-use a Logger instance using a configuration file.
    //! \author Matteo Valdina
    class LoggerFactory {
    private:
      class LoggerDeleter {
      public:
        void operator()(Logger* ptr) { delete ptr; }
      };

    protected:
      static LoggerFactory* _instance;
      static std::once_flag* _once;
      std::recursive_mutex* _mtx;

      std::unordered_map<std::string, std::ostream*> _outputs;
      std::unordered_map<std::string, std::shared_ptr<Logger>> _loggers;

      // Default values.
      Logger::LoggerLevel _default_level = Logger::LEVEL_ERROR;

    public:
      //! Get a reference to a Logger instance.
      static std::shared_ptr<Logger> get_logger(char const* name);

      //! Get singleton instance of LoggerFactory.
      static LoggerFactory* get_instance(void);

      //! Read and configure the LoggerFactory from the given file.
      bool configure(std::string path);

      //! Convert level to enum value.
      static Logger::LoggerLevel conv_logger_level_from_string(std::string level);
      
    protected:
      //! Ctor not available, use get_instance static method.
      LoggerFactory(void);
      virtual ~LoggerFactory(void);

      void parse_logger_configuration(std::string cfg, std::string& level, std::ostream** output);
      std::ostream* parse_output_configuration(std::string cfg);

      // Move this method in a more generic Class/Headers.
      static std::string trim(const std::string &s) {
        auto  wsfront = std::find_if_not(s.begin(), s.end(), std::isspace);
        return std::string(wsfront, std::find_if_not(s.rbegin(), std::string::const_reverse_iterator(wsfront), [](int c){return std::isspace(c); }).base());
      }

    };
  }
}

#endif // SIP0X_UTILS_LOGGERMANAGER_HPP__
