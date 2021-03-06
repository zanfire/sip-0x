#include "parser/tokens/TokenRegex.hpp"
#include "parser/tokens/TokenIPv4.hpp"

#include "parser/Parser.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"
#include "utils/IniFile.hpp"

using namespace std;


void test_occurrences() {
  /*
  std::shared_ptr<TokenAbstract> token1;
  token1.reset(new TokenRegex("[a-z]+\\.txt"));
  std::shared_ptr<TokenAbstract> op1;
  op1.reset(new OpOccurrence(token1, 1, -1));


  std::shared_ptr<TokenAbstract> token2;
  token2.reset(new TokenRegex("[a-z]+\\.doc"));
  std::shared_ptr<TokenAbstract> op2;
  op2.reset(new OpOccurrence(token2, 1, 1));


  std::shared_ptr<TokenAbstract> op;
  op.reset(new OpAlternative());

  dynamic_cast<OpAlternative*>(op.get())->add(op1);
  dynamic_cast<OpAlternative*>(op.get())->add(op2);


  Parser parser(op);
  
  run(parser, std::string("subject.doc"));
  run(parser, std::string("subject.txt"));
  run(parser, std::string("subject.txtsubject.txtsubject.txt"));
  run(parser, std::string("a aa aa subject.doc"));
  run(parser, std::string("subject.txt sedfsfsfs"));


  std::shared_ptr<TokenAbstract> ipv4;
  ipv4.reset(new TokenIPv4());
  Parser parser2(ipv4);
  run(parser2, std::string("10.0.2.13"));
  */
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
}