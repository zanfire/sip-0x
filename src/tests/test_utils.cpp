#include "test_prototypes.h"

#include "parser/factory/FactoryContext.hpp"
#include "parser/Parser.hpp"

#include <chrono>
using namespace sip0x::parser;

void run_test(TokenAbstract& token, std::string input, bool exp, bool factory) {
  cout << "Parsing string \"" << input << "\" .................. ";
  FactoryContext ctx;
  InputTokenStream iss(input);
  ParserResult r = parse(iss, token, &ctx);

  cout << "res: " << ((r.success()) ? "OK" : "KO");
  cout << ", exp: " << ((exp) ? "OK" : "KO");
  cout << ", so: " << ((r.success() == exp) ? "OK" : "KO") << std::endl;

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


void run_sip(std::string input) {
  //cout << "Parsing string\n" << input << "\n";
  InputTokenStream iss(input);
  
  auto t1 = std::chrono::high_resolution_clock::now();
  std::shared_ptr<sip0x::SIPMessage> message = parse(iss);
  auto t2 = std::chrono::high_resolution_clock::now();

  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
  std::cout << "Parsed in " << ms.count() << "ms\n";
  
  bool successes = message != nullptr;
  cout << "res: " << ((successes) ? "OK" : "KO");

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
