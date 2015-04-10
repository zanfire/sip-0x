#include "utils/ConnectionManager.hpp"

#include "utils/Connection.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"


using namespace sip0x::utils;

ConnectionManager::ConnectionManager(void) {
  _logger = LoggerFactory::get_instance()->get_logger("sip0x.ConnectionManager");
}

ConnectionManager::~ConnectionManager(void) {
}

void ConnectionManager::add(std::shared_ptr<Connection>& connection) {
  _mtx.lock();
  _connections.insert(connection);
  _mtx.unlock();
  // Start reading from connection.
  connection->async_read();
  //connection->open();
}

void ConnectionManager::remove(std::shared_ptr<Connection>& connection) {
  _mtx.lock();
  _connections.erase(connection);
  _mtx.unlock();
  connection->close();
}


std::shared_ptr<Connection> ConnectionManager::get(uint32_t remote_ip, uint16_t remote_port) {
  _mtx.lock();
  std::shared_ptr<Connection> connection;
  for (auto conn : _connections) {
    if (conn->get_remote_ip() == remote_ip && conn->get_remote_port() == remote_port) {
      connection = conn;
      break;
    }
  }
  _mtx.lock();
  void* c = connection.get();
  LOG_DEBUG(_logger, "Searching a connection %hhu.%hhu.%hhu.%hhu:%hu, result %p.", (unsigned char)(remote_ip >> 24), (unsigned char)(remote_ip >> 16), (unsigned char)(remote_ip >> 8), (unsigned char)(remote_ip), remote_port, connection.get());
  return connection;
}
