#include "test_prototypes.h"

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
  cout << "Parsing string \"" << input << "\" .................. ";
  FactoryContext ctx;
  Sip0x::Protocol::SIPMessage* message = Sip0x::Parser::parse_sip_message(input);
  bool successes = message != nullptr;
  cout << "res: " << ((successes) ? "OK" : "KO");

  if (message != nullptr) {
    delete message;
  }

  /*
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
  */
}
