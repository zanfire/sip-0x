#include "test_prototypes.h"

#include "parser/base/TokenRegex.hpp"
#include "parser/common/RegexConstStrings.hpp"
#include "parser/common/TokenPresets.hpp"

#include "parser/sip/TokenSIPMessage.hpp"
#include "parser/Parser.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"
#include "utils/IniFile.hpp"

using namespace Sip0x::Parser;
using namespace Sip0x::Utils;
using namespace Sip0x::Utils::Log;
using namespace std;

void test_token_regexconststrings() {
  {
    TokenRegex token("unreserved", RegexConstStrings::unreserved + "+");
    run_test(token, "pippo@dom.cnx", true);
    run_test(token, "pipp*o@dom.cnx", true);
    run_test(token, "@dom.cnx", false);
    run_test(token, " @", false);
  }
  {
    TokenRegex token(RegexConstStrings::token);
    run_test(token, "pippo", true);
    run_test(token, "~pipp*o", true);
    //csfsgsdg questo non dovrebbe passare
    run_test(token, "~pi@pp*o", false);

  }
  //run_test(token, "10.0.2.13x", false);
  //run_test(token, "10.0.2", false);
}

void test_token_ipv4() {
  TokenIPv4 ipv4;
  
  run_test(ipv4, "10.0.2.13", true);
  run_test(ipv4, "10.0.2.13x", false);
  run_test(ipv4, "10.0.2", false);
  run_test(ipv4, "0.0.0.0", true);
  run_test(ipv4, "255.255.255.255", true);
  run_test(ipv4, "255.255.255.258", false);
}


void test_token_sipuri() {
  TokenUserInfo t;

  run_test(t, "matteo:password@", true);
  run_test(t, "bhooo", false);
  run_test(t, "mat%20%23teo:password@", true);
  run_test(t, "matteo@", true);

  TokenURIParam_transport p;
  run_test(p, "transport=PROTOCOLPIPPO", true);

  TokenHost host;
  run_test(host, "domain.topdom", true);
  run_test(host, "10.0.6.11", true);


  TokenHostport hostport;
  run_test(hostport, "domain.topdom:5060", true);
  run_test(hostport, "10.0.6.15:5060", true);

  TokenSIPURI sipuri;
  run_test(sipuri, "sip:matteo:password@domain.top:5060;transport=tcp", true);
  run_test(sipuri, "sip:matteo@10.0.1.1:5060;transport=tcp", true);
  run_test(sipuri, "sip:matteo@10.0.1.1", true);
  run_test(sipuri, "sip:matteo@10.0.1.1:xy;transport=tcp", false);
  run_test(sipuri, "matteo@10.0.1.1", false);
}


void test_token_sip_message() {
  TokenSIPRequestLine rl;

  run_test(rl, "INVITE sip:matteo@domain.cmx SIP/2.0\r\n", true);
  run_test(rl, "INVITE sip:matteo@domain.cmx SIP/2.1\r\n", true);
  run_test(rl, "INVITE   sip:matteo@domain.cmx SIP/2.0\r\n", false);
  run_test(rl, "INVITE sip:matteo@domain.cmx XSIP/2.0\r\n", false);

  TokenSIPMessageHeader_From from;
  run_test(from, "From: Alice <sip:alice@atlanta.com>;tag=1928301774", true);

  TokenSIPMessageHeader_Contact_param contact_param;
  run_test(contact_param, "<sip:alice@pc33.atlanta.com>", true);

  TokenSIPMessageHeader_Contact contact;
  run_test(contact, "Contact: <sip:alice@pc33.atlanta.com>", true);

}