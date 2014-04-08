#include <iostream>

// asio test
//#define _WIN32_WINNT 0x0501
//#define ASIO_STANDALONE
//#include <asio.hpp>

//#include "parser/SIPParser.hpp"
#include "parser/Parser.hpp"

using namespace Sip0x::Parser;
using namespace std;

int main(int argc, char const* argv[]) {


  std::cout << "Give me a comma separated list of numbers.\n";
  std::cout << "Type [q or Q] to quit\n\n";

  std::string str;

  ParserX parser;
  std::string result;
  while (getline(std::cin, str))
  {
    if (str.empty() || str[0] == 'q' || str[0] == 'Q')
      break;

    str = "ACK sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKnashds9\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710\r\n";
    str += "CSeq: 314159 ACK\r\n";
    str += "Content-Length: 0\r\n";
    str += "\r\n";


    bool r = parser.parse(str);
    if (r)
    {
      std::cout << "OK\n";

    }
    else
    {
      std::cout << "FAILED\n";
    }
  }

  std::cout << "Bye... :-) \n\n";
  return 0;
}

