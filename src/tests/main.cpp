#include <iostream>

// asio test
//#define _WIN32_WINNT 0x0501
//#define ASIO_STANDALONE
//#include <asio.hpp>

#include "parser/SIPGrammar.hpp"

#include "parser/private/TokenRegex.hpp"


#include "utils/logs/Logger.hpp"

using namespace Sip0x::Parser;
using namespace Sip0x::Utils::Log;
using namespace std;

int main(int argc, char const* argv[]) {
  std::string str;

  Logger* logger = new Logger(&cout);

  LOGE(logger, "Initializing logger...");

  delete logger;

  /*
  // Simple regular expression matching
  std::string fnames[] = { "foo.txt", "bar.txt", "baz.dat", "zoidberg" };
  std::regex txt_regex("[a-z]+\\.txt");

  for (const auto &fname : fnames) {
    std::cout << fname << ": " << std::regex_match(fname, txt_regex) << '\n';
  }

  // Extraction of a sub-match
  std::regex base_regex("([a-z]+)\\.txt");
  std::smatch base_match;

  for (const auto &fname : fnames) {
    if (std::regex_match(fname, base_match, base_regex)) {
      // The first sub_match is the whole string; the next
      // sub_match is the first parenthesized expression.
      if (base_match.size() == 2) {
        std::ssub_match base_sub_match = base_match[1];
        std::string base = base_sub_match.str();
        std::cout << fname << " has a base of " << base << '\n';
      }
    }
  }

  // Extraction of several sub-matches
  std::regex pieces_regex("([a-z]+)\\.([a-z]+)");
  std::smatch pieces_match;

  for (const auto &fname : fnames) {
    if (std::regex_match(fname, pieces_match, pieces_regex)) {
      std::cout << fname << '\n';
      for (size_t i = 0; i < pieces_match.size(); ++i) {
        std::ssub_match sub_match = pieces_match[i];
        std::string piece = sub_match.str();
        std::cout << "  submatch " << i << ": " << piece << '\n';
      }
    }
  }

  TokenRegex t("[a-z]+\\.txt");
  t.parse("aa aaa subject.txt");
  */
  SIPGrammar grammar;
  std::string result;
  
  /*
  str = "ACK sip:bob@192.0.2.4 SIP/2.0\r\n";
  str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKnashds9\r\n";
  str += "Max-Forwards: 70\r\n";
  str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
  str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
  str += "Call-ID: a84b4c76e66710\r\n";
  str += "CSeq: 314159 ACK\r\n";
  str += "Content-Length: 0\r\n";
  str += "\r\n";
  //std::cout << "Parsing :" << str << endl;
  bool r = parser.parse(str);
  std::cout << (r ? "OK" : "KO") << endl;


  str = "ACK sip:bob@192.0.2.4 SIP/2.0\r\n";
  str += "Max-Forwards: 70\r\n";
  str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
  str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
  str += "Call-ID: a84b4c76e66710\r\n";
  str += "CSeq: 314159 ACK\r\n";
  str += "Content-Length: 0\r\n";
  str += "\r\n";
  //std::cout << "Parsing :" << str << endl;
  r = parser.parse(str);
  std::cout << (r ? "OK" : "KO") << endl;

  str = "ACK sip:bob@192.0.2.4 SIP/2.0\r\n";
  str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKnashds9\r\n";
  str += "Content-Length: 0\r\n";
  str += "\r\n";
  std::cout << "Parsing :" << str << endl;
  r = parser.parse(str);
  std::cout << (r ? "OK" : "KO") << endl;
  
  str = "Contact: alice <sip:alice@pc33.atlanta.com>";
  std::cout << "Parsing :" << str << endl;
  r = parser.parse(str);
  std::cout << (r ? "OK" : "KO") << endl;

 
  str = "alice <sip:alice@pc33.atlanta.com>";
  std::cout << "Parsing :" << str << endl;
  r = parser.parse(str);
  std::cout << (r ? "OK" : "KO") << endl;

  str = "<sip:alice@pc33.atlanta.com>";
  std::cout << "Parsing :" << str << endl;
  r = parser.parse(str);
  std::cout << (r ? "OK" : "KO") << endl;

  */

  str = "sip:bob@192.0.2.4";
  std::cout << "Parsing: " << str;
  bool r = grammar.parse(str);
  std::cout << " ---> " << (r ? "OK" : "KO") << endl;

  getline(std::cin, str);
  return 0;
}

