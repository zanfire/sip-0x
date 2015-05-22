#include "SIPParserTest.hpp"

#include "parser/Parser.hpp"

using namespace unittests;

SIPParserTest::SIPParserTest(void) : BaseTest("Parser", "Test of SIP parser.") {
}


SIPParserTest::~SIPParserTest(void) {
}


void SIPParserTest::prepare(void) {
  sip0x::parser::Parser::load_grammar();
}


bool SIPParserTest::execute(void) {
  std::string str;
  str = "ACK sip:bob@192.0.2.4 SIP/2.0\r\n";
  str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKnashds9\r\n";
  str += "Max-Forwards: 70\r\n";
  str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
  str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
  str += "Call-ID: a84b4c76e66710\r\n";
  str += "CSeq: 314159 ACK\r\n";
  str += "Content-Length: 0\r\n";
  str += "\r\n";
  
  std::shared_ptr<sip0x::protocol::SIPMessage> message = sip0x::parser::Parser::parse()
}
