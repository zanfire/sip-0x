#include "test_prototypes.h"

#include "parser/base/TokenRegex.hpp"
#include "parser/common/RegexConstStrings.hpp"
#include "parser/common/TokenIPv4.hpp"
#include "parser/sip/TokenUserInfo.hpp"
#include "parser/sip/TokenURIParameter.hpp"


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
}