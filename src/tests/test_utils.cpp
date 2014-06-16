#include "test_prototypes.h"

void run_test(std::shared_ptr<TokenAbstract> token, std::string input, bool exp) {
  Parser parser(token);
  bool r = parser.parse(input);
  cout << "Parsing string \"" << input << "\" .................. ";
  cout << "res: " << ((r)         ? "OK" : "KO");
  cout << ", exp: " << ((exp)     ? "OK" : "KO");
  cout << ", so: " << ((r == exp) ? "OK" : "KO") << std::endl;
}


void run_test(Parser& parser, std::string input, bool exp) {
  bool r = parser.parse(input);
  cout << "Parsing string \"" << input << "\" .................. ";
  cout << "res: " << ((r) ? "OK" : "KO");
  cout << ", exp: " << ((exp) ? "OK" : "KO");
  cout << ", so: " << ((r == exp) ? "OK" : "KO") << std::endl;
}
