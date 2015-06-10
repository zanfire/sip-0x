#include "TransportLayerMock.hpp"

using namespace sip0x;
using namespace mocks;

TransportLayerMock::TransportLayerMock(void) {

}


TransportLayerMock::~TransportLayerMock(void) {

}

void TransportLayerMock::send(std::shared_ptr<sip0x::Transaction>& transaction, std::shared_ptr<sip0x::protocol::SIPMessage> const& message){

}


void TransportLayerMock::on_receive(std::shared_ptr<sip0x::protocol::SIPMessage> const& message) {

}