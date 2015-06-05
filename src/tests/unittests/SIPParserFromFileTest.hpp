#if !defined(SIP0X_SIPPARSERFROMFILETEST_HPP__)
#define SIP0X_SIPPARSERFROMFILETEST_HPP__

#include "BaseTest.hpp"

#include <string>
#include <memory>

#include "parser/Parser.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/InputTokenStream.hpp"

namespace unittests
{
  //! Model unit test interface.
  class SIPParserFromFileTest : public BaseTest {
  protected:
    std::string _path;
    bool break_on_error = false;

  public:
    SIPParserFromFileTest(std::string const& path) : 
      BaseTest("SIP Parser from file", "Test SIP parser reading message from a file."), _path(path) {
    }
    
    virtual ~SIPParserFromFileTest(void) {}

    bool run_sip(std::string input) {
      //cout << "Parsing string\n" << input << "\n";
      sip0x::utils::InputTokenStream iss(input);

      auto t1 = std::chrono::high_resolution_clock::now();
      std::shared_ptr<sip0x::protocol::SIPMessage> message = sip0x::parser::Parser::parse(iss);
      auto t2 = std::chrono::high_resolution_clock::now();

      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
      if (message != nullptr) {
        std::cout << "Successfully parsed SIP message in " << ms.count() << "ms\n";
        return true;
      }
      else {
        std::cout << "Failed parsed SIP message in " << ms.count() << "ms\n";
        return false;
      }

      /*
      res: OKParsed in 93ms
      res: OKParsed in 140ms
      res: OKParsed in 46ms
      res: OKParsed in 218ms
      res: OKParsed in 843ms
      res: OKParsed in 375ms
      res: OKParsed in 484ms

      Parsed in 328ms
      res: OKParsed in 78ms
      res: OKParsed in 140ms
      res: OKParsed in 31ms
      res: OKParsed in 187ms
      res: OKParsed in 718ms
      res: OKParsed in 328ms
      res: OKParsed in 390ms
      */

      //if (message != nullptr) {
      //  std::cout << std::endl;
      //  message->write(std::cout);
      //  std::cout << std::endl;
      //  delete message;
      //}
    }
  
    virtual void prepare(void) override {}
    
    virtual bool execute(void) override {
      std::shared_ptr<sip0x::utils::Logger> logger = sip0x::utils::LoggerFactory::get_logger("Test.sipmessages");

      std::ifstream ifs(_path, std::ifstream::in);
      if (!ifs.is_open()) {
        LOG_ERROR(logger, "Failed to open INI file [%s].", _path);
        return false;
      }

      char const* begin_marker = "--BEGIN--";
      char const* end_marker = "--END--";

      std::string line;
      std::string content;

      bool reading_content = false;
      while (ifs.good()) {
        std::getline(ifs, line);

        if (!reading_content && line.compare(begin_marker) == 0) {
          content = "";
          reading_content = true;
        }
        else if (reading_content && line.compare(end_marker) == 0) {
          bool result = run_sip(content);
          if (break_on_error && !result) {
            break;
          }
          reading_content = false;
        }
        else if (reading_content) {
          content += line + "\r\n";
        }
      }

      return true;
    }
  };
}

#endif // SIP0X_SIPPARSERFROMFILETEST_HPP__
