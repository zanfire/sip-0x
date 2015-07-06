#include "TransportLayerTCP.hpp"

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


TransportLayerTCP::TransportLayerTCP(std::string const& bind_address, int bind_port) :
  ConnectionListener(),
  sip0x::utils::enable_protected_dtor<TransportLayerTCP>(),
  std::enable_shared_from_this<TransportLayerTCP>(),
  sip0x::utils::ThreadedObject(),
  sip0x::TransportLayer(),
  _bind_address(bind_address),
  _bind_port(bind_port),
  _io_service(),
  _tcp_socket(_io_service), 
  _acceptor(_io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), bind_port)) {
}

TransportLayerTCP::~TransportLayerTCP() {
}


void TransportLayerTCP::process(void) {
  LOG_DEBUG(_logger, "Start processing thread.");
  while (!_thread_must_stop) {
    // Install async operation.
    async_accept();
    // process async operation.
    _io_service.run();
  }
  LOG_DEBUG(_logger, "End processing thread.");
}


void TransportLayerTCP::async_accept(void) {
  // TODO: Remove recursion after awhile this bring to a stack overflow.
  _acceptor.async_accept(_tcp_socket, [this](std::error_code ec) {
    if (!ec) {
      _connection_manager.add(Connection::create(_tcp_socket, std::dynamic_pointer_cast<sip0x::listeners::ConnectionListener>(shared_from_this())));
    }
    async_accept();
  });
}


void TransportLayerTCP::send(std::shared_ptr<Transaction>& transaction, std::shared_ptr<const sip0x::protocol::SIPMessage>&  message) {
  std::string msg = message->to_string();
  std::shared_ptr<RemotePeerTCP> remote = std::static_pointer_cast<RemotePeerTCP>(transaction->remotepeer);

  LOG_INFO(_logger_siptrace, "Send\n----\n%s\n----", message->to_string().c_str());

  if (message->is_request) {
    if (remote == nullptr) {
      std::shared_ptr<const SIPRequest> request = std::dynamic_pointer_cast<const SIPRequest>(message);
      // Get destination from ReqeustURI.
      std::string host = request->uri.hostport.host;
      int port = request->uri.hostport.port;

      remote = std::make_shared<RemotePeerTCP>();
      remote->connection = _connection_manager.get(resolve(host), port);
      if (remote->connection == nullptr) {
        LOG_INFO(_logger, "Connection to %s:%d doesn't exists, trying to connect to remote host.", host.c_str(), port);
        remote->connection = connect(host, port);
      }
    }
  }
  else {
    std::shared_ptr<const SIPResponse> response = std::dynamic_pointer_cast<const SIPResponse>(message);

    /*
        The server transport uses the value of the top Via header field in
        order to determine where to send a response.  It MUST follow the 
        following process:
          - If the "sent-protocol" is a reliable transport protocol such as
          TCP or SCTP, or TLS over those, the response MUST be sent using
          the existing connection to the source of the original request
          that created the transaction, if that connection is still open.
          This requires the server transport to maintain an association
          between server transactions and transport connections.  If that
          connection is no longer open, the server SHOULD open a
          connection to the IP address in the "received" parameter, if
          present, using the port in the "sent-by" value, or the default
          port for that transport, if no port is specified.  If that
          connection attempt fails, the server SHOULD use the procedures
          in [4] for servers in order to determine the IP address and
          port to open the connection and send the response to.
          */
    /*
          - Otherwise, if the Via header field value contains a "maddr"
          parameter, the response MUST be forwarded to the address listed
          there, using the port indicated in "sent-by", or port 5060 if
          none is present.  If the address is a multicast address, the
          response SHOULD be sent using the TTL indicated in the "ttl"
          parameter, or with a TTL of 1 if that parameter is not present.
          */
    auto via = response->get_first<SIPMessageHeaderVia>();
    //std::string maddr = via->params[std::string("maddr")];
    /*
          -  Otherwise (for unreliable unicast transports), if the top Via
          has a "received" parameter, the response MUST be sent to the
          address in the "received" parameter, using the port indicated
          in the "sent-by" value, or using port 5060 if none is specified
          explicitly.  If this fails, for example, elicits an ICMP "port
          unreachable" response, the procedures of Section 5 of [4]
          SHOULD be used to determine where to send the response.
                
          - Otherwise, if it is not receiver-tagged, the response MUST be
          sent to the address indicated by the "sent-by" value, using the
          procedures in Section 5 of [4].
          
    */


          
    //response->
    // Get destination from ReqeustURI.
    //std::string host = request->uri.hostport.host;
    //int port = request->uri.hostport.port;
    // Check if for this destination is present a connection.
    // Try to connect.
          
    //conn = (Connection*)opaque_data;

  }

  if (remote != nullptr) {
    remote->connection->async_write((unsigned char*)msg.c_str(), msg.length());
  }
  else {
    // Fail-back on UDP.
    // Try to shrink message.
    // Chunking UDP 
    // Send chunks
  }
}


void TransportLayerTCP::on_incoming_data(std::shared_ptr<utils::Connection> conn, uint8_t const* buffer, std::size_t const size) {
  utils::InputTokenStream iss(buffer, size);
  std::shared_ptr<sip0x::protocol::SIPMessage> message = sip0x::parser::Parser::parse(iss);

  if (message == nullptr) {
    if (_logger_siptrace->get_level() >= Logger::LEVEL_DEBUG) {
      LOG_DEBUG(_logger_siptrace, "Received un-decoded data: %s", iss.str().c_str());
    }
    else {
      LOG_WARN(_logger_siptrace, "Received un-decoded data.");
    }
    return;
  }
  else {
    LOG_INFO(_logger_siptrace, "Recv\n----\n%s\n----", message->to_string().c_str());
  }
  std::shared_ptr<RemotePeerTCP> remote = std::make_shared<RemotePeerTCP>();
  remote->connection = conn;

  received.emit(message, std::static_pointer_cast<RemotePeer>(remote));
}

std::shared_ptr<Connection> TransportLayerTCP::connect(std::string const& address, int port) {
  asio::ip::tcp::resolver resolver(_io_service);
  auto endpoint_iterator = resolver.resolve({ address, std::to_string(port) });

  std::shared_ptr<Connection> connection = Connection::create(_tcp_socket, std::dynamic_pointer_cast<sip0x::listeners::ConnectionListener>(shared_from_this()));
  connection->connect(endpoint_iterator);
  _connection_manager.add(connection);
  return connection;
}


uint32_t TransportLayerTCP::resolve(std::string const& address) {
  asio::ip::tcp::resolver resolver(_io_service);
  asio::ip::tcp::resolver::query query(address, "");
  for (asio::ip::tcp::resolver::iterator i = resolver.resolve(query); i != asio::ip::tcp::resolver::iterator(); ++i)
  {
    asio::ip::tcp::endpoint end = *i;
    return end.address().to_v4().to_ulong();
  }
  return 0;
}
