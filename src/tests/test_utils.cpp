#include "test_prototypes.h"

void run_test(TokenAbstract& token, std::string input, bool exp) {
  cout << "Parsing string \"" << input << "\" .................. ";
  
  Sip0x::Parser::ReadResult r = Sip0x::Parser::parse(input, token);

  cout << "res: " << ((r.successes) ? "OK" : "KO");
  cout << ", exp: " << ((exp) ? "OK" : "KO");
  cout << ", so: " << ((r.successes == exp) ? "OK" : "KO") << std::endl;

  if (!r.successes) {
    cout << endl << input << endl;
    cout.width(r.errorpos);
    cout << '^' << endl;


    cout << "Parsing error (pos: " << r.errorpos << ") message: " << r.errormessage << endl;
  }
}
