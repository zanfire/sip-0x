#include "TransactionTest.hpp"

#include "parser/Parser.hpp"
#include "utils/InputTokenStream.hpp"
#include "utils/Clock.hpp"

#include "TransactionLayer.hpp"
#include "Transaction.hpp"

using namespace sip0x;
using namespace unittests;
using namespace mocks;

TransactionTest::TransactionTest(void) : BaseTest("Transaction", "Test for Transaction.") {
}


TransactionTest::~TransactionTest(void) {
}


void TransactionTest::prepare(void) {
  _transport = std::make_shared<mocks::TransportLayerMock>();
}


bool TransactionTest::execute(void) {
  sip0x::TransactionLayer tl(std::dynamic_pointer_cast<sip0x::TransportLayer>(_transport));
  
  char const* reg_message = "REGISTER sip:127.0.0.1:5060 SIP/2.0\r\n" \
        "Via : SIP/2.0/TCP 127.0.0.1;branch=z9hG4bK_unittest\r\n" \
        "Max-Forwards: 70\r\n" \
        "User-Agent: sip0x - ua\r\n" \
        "CSeq: 1 REGISTER\r\n" \
        "Call-ID : ecfVebFtpkEApbV@127.0.0.1\r\n" \
        "Content-Length: 0\r\n" \
        "Expires: 3\r\n" \
        "\r\n";
  char const* res_message = "SIP/2.0 200 OK\r\n" \
    "Via : SIP/2.0/TCP 127.0.0.1;branch=z9hG4bK_unittest\r\n" \
    "Max-Forwards: 70\r\n" \
    "User-Agent: sip0x - ua\r\n" \
    "CSeq: 1 REGISTER\r\n" \
    "Call-ID : ecfVebFtpkEApbV@127.0.0.1\r\n" \
    "Content-Length: 0\r\n" \
    "\r\n";


  _transport->inject_message((uint8_t const*)reg_message, std::strlen(reg_message));
  // We expect that SIP request is accepted and TR is in TRYNG state.
  auto transaction = tl.get_transaction("REGISTER_z9hG4bK_unittest");
  if (transaction->state != TransactionState::TRANSACTION_STATE_TRYING) return false;
  _transport->inject_message((uint8_t const*)res_message, std::strlen(reg_message));
  if (transaction->state != TransactionState::TRANSACTION_STATE_COMPLETED) return false;
  sip0x::utils::Clock::add_offset(8 * 1000);
  tl.on_process();
  if (transaction->state != TransactionState::TRANSACTION_STATE_TERMINATED) return false;
  // Cleanup we expect that tran is dtor with this reset.
  transaction.reset();

  auto msg = _transport->get_last_message();
  return true;
}


