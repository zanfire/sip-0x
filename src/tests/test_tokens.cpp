#include "test_prototypes.h"

#include "parser/common/TokenIPv4.hpp"
#include "parser/sip/TokenUserInfo.hpp"


#include "parser/Parser.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"
#include "utils/IniFile.hpp"

using namespace Sip0x::Parser;
using namespace Sip0x::Utils;
using namespace Sip0x::Utils::Log;
using namespace std;

void test_token_ipv4() {
  std::shared_ptr<TokenAbstract> ipv4;
  ipv4.reset(new TokenIPv4());
  Parser parser(ipv4);
  
  run_test(parser, "10.0.2.13", true);
  run_test(parser, "10.0.2.13x", false);
  run_test(parser, "10.0.2", false);
  run_test(parser, "0.0.0.0", true);
  run_test(parser, "255.255.255.255", true);
  run_test(parser, "255.255.255.258", false);
}


void test_token_sipuri() {
  std::shared_ptr<TokenAbstract> t;
  t.reset(new TokenUserInfo());
  Parser parser(t);


  run_test(parser, "matteo:password@", true);
  run_test(parser, "bhooo", false);
  run_test(parser, "matteo@", true);
}