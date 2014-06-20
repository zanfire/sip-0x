#include "test_prototypes.h"

void run_test(TokenAbstract& token, std::string input, bool exp) {
  cout << "Parsing string \"" << input << "\" .................. ";
  
  bool r = Sip0x::Parser::parse(input, token, std::cout);

  cout << "res: " << ((r) ? "OK" : "KO");
  cout << ", exp: " << ((exp) ? "OK" : "KO");
  cout << ", so: " << ((r == exp) ? "OK" : "KO") << std::endl;
}
