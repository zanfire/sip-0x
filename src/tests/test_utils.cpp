#include "test_prototypes.h"

#include "parser/factory/FactoryContext.hpp"
#include "parser/Parser.hpp"

#include <chrono>
using namespace sip0x::parser;

static bool verbose = false;
static bool only_failed = true;

void run_test(TokenAbstract& token, std::string input, bool exp, bool factory) {
  FactoryContext ctx;
  InputTokenStream iss(input);
  ParserResult r = Parser::parse(iss, token, &ctx);

  if (r.success() != exp || !only_failed) {
    std::cout << "Test input: " << (verbose ? input : input.substr(0, 20)) << " \t\t" << ((r.success() == exp) ? "Passed" : "Failed") << std::endl;
  }
  if (verbose) {
    if (r.success() != exp) {
      if (!r.success()) {

        ParserResult::ParserEvent ev = r.get_error();
        cout << endl;
        for (std::size_t i = 0; i < input.length(); i++) {
          std::size_t x = i;
          while (x < input.length()) {
            cout << input[x];
            if (input[x] == '\n') break;
            x++;
          }

          if (i <= ev.position && ev.position <= x) {
            cout.width(ev.position - i);
            if (input[x] != '\n') {
              cout << endl;
            }
            cout << '^' << endl;
          }
          i = x;
        }

        cout << "Parsing error (pos: " << ev.position << ") message: " << ev.message << endl;
      }
    }
  }
}


void run_sip(std::string input) {
  //cout << "Parsing string\n" << input << "\n";
  InputTokenStream iss(input);
  
  auto t1 = std::chrono::high_resolution_clock::now();
  std::shared_ptr<sip0x::SIPMessage> message = Parser::parse(iss);
  auto t2 = std::chrono::high_resolution_clock::now();

  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
  if (message != nullptr) {
    std::cout << "Successfully parsed SIP message in " << ms.count() << "ms\n";
  }
  else {
    std::cout << "Failed parsed SIP message in " << ms.count() << "ms\n";
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
