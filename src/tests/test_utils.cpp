#include "test_prototypes.h"

#include <chrono>

void run_test(TokenAbstract& token, std::string input, bool exp, bool factory) {
  cout << "Parsing string \"" << input << "\" .................. ";
  FactoryContext ctx;
  Sip0x::Parser::ReadResult r = Sip0x::Parser::parse(input, token, &ctx);

  cout << "res: " << ((r.successes) ? "OK" : "KO");
  cout << ", exp: " << ((exp) ? "OK" : "KO");
  cout << ", so: " << ((r.successes == exp) ? "OK" : "KO") << std::endl;

  if (!r.successes) {
    cout << endl;
    for (int i = 0; i < (int)input.length(); i++) {
      int x = i;
      while (x < (int)input.length()) {
        cout << input[x];
        if (input[x] == '\n') break;
        x++;
      }

      if (i <= r.errorpos && r.errorpos <= x) {
        cout.width(r.errorpos - i);
        if (input[x] != '\n') {
          cout << endl;
        }
        cout << '^' << endl;
      }
      i = x;
    }

    cout << "Parsing error (pos: " << r.errorpos << ") message: " << r.errormessage << endl;
  }
}


void run_sip(std::string input) {
  //cout << "Parsing string\n" << input << "\n";
  FactoryContext ctx;
  
  auto t1 = std::chrono::high_resolution_clock::now();
  Sip0x::SIPMessage* message = Sip0x::Parser::parse_sip_message(input);
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
