#include <iostream>

#include "test_prototypes.h"

#include "utils/log/LoggerManager.hpp"


#include "parser/base/Token.hpp"
#include "parser/base/Alternative.hpp"

using namespace Sip0x::Utils::Log;
using namespace std;


int main(int argc, char const* argv[]) {
  

  //Sip0x::Parser::Alternative<Token, Token, Token> alternative(Token("tcp"), Token("udp"), Token("sctp"));
  auto alternative = Sip0x::Parser::make_alternative(Token("tcp"), Token("udp"), Token("sctp"));

  Sip0x::Parser::parse("sctss", alternative, std::cout);

  std::string str;
  LoggerManager* loggermanager = LoggerManager::get_instance();
  loggermanager->configure("..\\docs\\logger.ini");
  
  test_token_sipuri();

  test_token_regexconststrings();
  test_token_ipv4();
  test_occurrences();
  
  getline(std::cin, str);
  return 0;
}