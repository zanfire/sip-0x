#include "utils/Connection.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

#include "asio_header.hpp"

#include "listeners/ConnectionListener.hpp"

#include <functional>

using namespace sip0x::utils;

Connection::Connection(asio::ip::tcp::socket& socket, const std::shared_ptr<sip0x::listeners::ConnectionListener>& listener) :
  _socket(std::move(socket)), _listener(listener) {
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


void Connection::close(void) {
}


void Connection::async_connect(asio::ip::tcp::resolver::iterator endpoint_iterator) {
  asio::async_connect(_socket, endpoint_iterator,
    [this](std::error_code ec, asio::ip::tcp::resolver::iterator)
  {
    LOG_DEBUG(_logger, "Async connection result: %d - %s", ec.value(), ec.message().c_str());
  });
}

void Connection::async_read(void) {
  _socket.async_read_some(asio::buffer(_rbuffer, sizeof(_rbuffer)), std::bind(&Connection::handle_read, this, std::placeholders::_1, std::placeholders::_2));
}

void Connection::async_write(unsigned char* buffer, std::size_t length) {
  std::memcpy(_wbuffer, buffer, length);
  auto self(shared_from_this());
  _socket.async_write_some(asio::buffer(_wbuffer, length), std::bind(&Connection::handle_write, this, std::placeholders::_1, std::placeholders::_2));
}


void Connection::handle_read(std::error_code ec, std::size_t length) {
  LOG_DEBUG(_logger, "Async read result: %d - %s, len: %lu", ec.value(), ec.message().c_str(), length);
  if (!ec) {
    _listener->on_incoming_data(shared_from_this(), _rbuffer, length);
    async_read();
  }
  else {
    // Stops read from this socket.
    LOG_INFO(_logger, "Stop reading from connection@%p due to error %d - %s", this, ec.value(), ec.message().c_str());
  }
}

void Connection::handle_write(std::error_code ec, std::size_t length) {
  LOG_DEBUG(_logger, "Async write result: %d - %s, len: %lu", ec.value(), ec.message().c_str(), length);
  if (!ec) {
    //_socket.async_write_some(asio::buffer(_wbuffer, sizeof(_wbuffer)), handle_write);
  }
}
