#include "UASTest.hpp"

#include "parser/Parser.hpp"
#include "utils/InputTokenStream.hpp"

#include "TransactionLayer.hpp"
#include "UAS.hpp"

using namespace sip0x;
using namespace unittests;
using namespace mocks;

UASTest::UASTest(void) : BaseTest("UAS", "Test for UAS.") {
}


UASTest::~UASTest(void) {
}


void UASTest::prepare(void) {
  _transport = std::make_shared<mocks::TransportLayerMock>();
}


bool UASTest::execute(void) {
  sip0x::TransactionLayer tl(std::dynamic_pointer_cast<sip0x::TransportLayer>(_transport));
  sip0x::UAS uas(&tl, nullptr, "testnetwork.cnx", "unittest-ua");
  
  char const* reg_message = "REGISTER sip:127.0.0.1:5060 SIP/2.0\r\n" \
        "Via : SIP/2.0/TCP 127.0.0.1;branch=z9hG4bK_kMeJcNrmerawTLevhmvIUGMrklxsKMI\r\n" \
        "Max-Forwards: 70\r\n" \
        "User-Agent: sip0x - ua\r\n" \
        "CSeq: 1 REGISTER\r\n" \
        "Call-ID : ecfVebFtpkEApbV@127.0.0.1\r\n" \
        "Content-Length: 0\r\n" \
        "Expires: 3\r\n" \
        "\r\n";

  _transport->inject_message((uint8_t const*)reg_message, std::strlen(reg_message));
  auto msg = _transport->get_last_message();
  return false;
}


