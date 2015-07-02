#include "TransportLayerMock.hpp"

#include "utils/InputTokenStream.hpp"
#include "parser/Parser.hpp"


using namespace sip0x;
using namespace mocks;

TransportLayerMock::TransportLayerMock(void) {

}


TransportLayerMock::~TransportLayerMock(void) {

}

void TransportLayerMock::inject_message(uint8_t const* buffer, std::size_t size) {
  utils::InputTokenStream iss(buffer, size);
  std::shared_ptr<sip0x::protocol::SIPMessage> message = parser::Parser::parse(iss);

  if (message == nullptr) {
    return;
  }
  std::shared_ptr<RemotePeer> remote = std::make_shared<RemotePeer>();
  received.emit(message, remote);
}


void TransportLayerMock::send(std::shared_ptr<sip0x::Transaction>& transaction, std::shared_ptr<sip0x::protocol::SIPMessage> const& message) {
  // Mock received message dispatch to the testing 
}