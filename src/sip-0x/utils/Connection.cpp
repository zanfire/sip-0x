#include "Connection.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

#include "asio_header.hpp"

#include <string>
#include <memory>

using namespace sip0x;

Connection::Connection(asio::ip::tcp::socket socket, ConnectionManager* manager, ConnectionListener* listener) :
  _socket(std::move(socket)), _manager(manager), _listener(listener) {

  _logger = LoggerFactory::get_logger("sip0x.Connection");
}

Connection::~Connection(void) {
}

uint32_t Connection::get_remote_ip(void) {
  // TODO: Write better code for these steps.
  return _socket.remote_endpoint().address().to_v4().to_ulong();
}

uint16_t Connection::get_remote_port(void) {
  // TODO: Write better code for these steps.
  return _socket.remote_endpoint().port();
}


void Connection::connect(asio::ip::tcp::resolver::iterator endpoint_iterator) {
  asio::connect(_socket, endpoint_iterator);
}

void close(void) {

}

void Connection::async_connect(asio::ip::tcp::resolver::iterator endpoint_iterator) {
  asio::async_connect(_socket, endpoint_iterator,
    [this](std::error_code ec, asio::ip::tcp::resolver::iterator)
  {
    LOG_DEBUG(_logger, "Async connection result: %d - %s", ec.value(), ec.message().c_str());
    if (!ec)
    {
      //do_read_header();
    }
  });
}

void Connection::async_read(void) {
  auto self(shared_from_this());
  _socket.async_read_some(asio::buffer(_rbuffer, sizeof(_rbuffer)),
    [this, self](std::error_code ec, std::size_t length) {
    LOG_DEBUG(_logger, "Async read result: %d - %s", ec.value(), ec.message().c_str());
    if (!ec) {
      _listener->on_incoming_data(this, _rbuffer, length);
    }
  });
}

void Connection::async_write(unsigned char* buffer, std::size_t length) {
  std::memcpy(_wbuffer, buffer, length);
  auto self(shared_from_this());
  asio::async_write(_socket, asio::buffer(_wbuffer, length),
    [this, self](std::error_code ec, std::size_t /*length*/) {
    LOG_DEBUG(_logger, "Async write result: %d - %s", ec.value(), ec.message().c_str());
    if (!ec)
    {
    }
  });
}
