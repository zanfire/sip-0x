#include "parser/Parser.hpp"

#include "parser/private/SIPGrammar.hpp"

using namespace Sip0x::Parser;
using namespace std;


ParserX::ParserX(void) {

}


ParserX::~ParserX(void) {

}


bool ParserX::parse(string message) {
  // Instantiate SIP grammar
  typedef std::string::const_iterator iterator_type;
  typedef SIPGrammar<iterator_type> sip_parser;

  sip_parser grammar;
  std::string result;

  bool r = qi::parse(message.begin(), message.end(), grammar, result);

  //if (first != last) // fail if we did not get a full match

  if (r) {
    std::cout << "OK\n";
  }
  else {
    std::cout << "FAILED\n";
  }
  return 0;
}