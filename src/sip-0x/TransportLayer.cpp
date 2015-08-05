#include "TransportLayer.hpp"

#include "protocol/SIPMessage.hpp"
#include "Transaction.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"
#include "utils/Connection.hpp"
#include "utils/ConnectionManager.hpp"
#include "utils/InputTokenStream.hpp"

#include "parser/Parser.hpp"

using namespace sip0x;
using namespace sip0x::utils;
using namespace sip0x::protocol;


TransportLayer::TransportLayer(void) {
  _logger = LoggerFactory::get_logger("sip0x.transport");
  _logger_siptrace = LoggerFactory::get_logger("sip0x.siptrace");
}

TransportLayer::~TransportLayer(void) {
}
