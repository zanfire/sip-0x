#include <iostream>

// asio test
//#define _WIN32_WINNT 0x0501
//#define ASIO_STANDALONE
//#include <asio.hpp>

#include "parser/SIPGrammar.hpp"

#include "parser/private/TokenRegex.hpp"
#include "parser/private/OpAlternative.hpp"
#include "parser/private/OpOccurrence.hpp"

#include "parser/Parser.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"
#include "utils/IniFile.hpp"

using namespace Sip0x::Parser;
using namespace Sip0x::Utils;
using namespace Sip0x::Utils::Log;
using namespace std;

int main(int argc, char const* argv[]) {
  std::string str;
  LoggerManager* loggermanager = LoggerManager::get_instance();
  loggermanager->configure("..\\docs\\logger.ini");

  std::shared_ptr<Logger> logger = LoggerManager::get_logger("main");


  std::shared_ptr<TokenAbstract> token1;
  token1.reset(new TokenRegex("[a-z]+\\.txt"));
  std::shared_ptr<OpAbstract> op1;
  op1.reset(new OpOccurrence(token1, 1, 1));
  

  std::shared_ptr<TokenAbstract> token2;
  token2.reset(new TokenRegex("[a-z]+\\.doc"));
  std::shared_ptr<OpAbstract> op2;
  op2.reset(new OpOccurrence(token2, 1, 1));


  std::shared_ptr<OpAbstract> op;
  op.reset(new OpAlternative());
  
  dynamic_cast<OpAlternative*>(op.get())->add(op1);
  dynamic_cast<OpAlternative*>(op.get())->add(op2);


  Parser parser(op);
  parser.parse(std::string("subject.txt"));
  parser.parse(std::string("subject.doc"));
  parser.parse(std::string("aa aaa subject.txt"));
  parser.parse(std::string("subject.txt dsfsdgsg"));


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

