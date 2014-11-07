#if !defined(SIP0X_LOGIC_TRANSPORTLAYER_HPP__)
#define SIP0X_LOGIC_TRANSPORTLAYER_HPP__

#include "asio_header.hpp"

#include <string>
#include <memory>
#include <thread>

#include "logic/Connection.hpp"
#include "logic/ConnectionManager.hpp"
#include "logic/TransportListener.hpp"

#include "parser/SIPParser.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"

namespace sip0x
{
  namespace Logic
  {
    using namespace sip0x::Utils::Log;

    class TransportLayer : public ConnectionListener  {
    protected:
      // Infrastructure
      std::shared_ptr<Logger> _logger;
      std::shared_ptr<Logger> _logger_siptrace;
      std::string _bind_address;
      int _bind_port;
      bool _thread_must_stop = false;
      // Threading
      std::thread* _thread = nullptr;
      // Network
      asio::io_service _io_service;
      asio::ip::tcp::socket _tcp_socket;
      //asio::ip::udp::socket _udp_socket; 
      asio::ip::tcp::acceptor _acceptor;
      ConnectionManager _connection_manager;
      // Parser
      sip0x::Parser::SIPParser parser;
      // Callbakcs
      TransportListener* _listener = nullptr;

    public:
      //! \todo Use bind address
      TransportLayer(std::string const& bind_address, int const& bind_port) :
        ConnectionListener(),
        _bind_address(bind_address),
        _bind_port(bind_port),
        _thread(),
        _io_service(),
        _tcp_socket(_io_service), 
        _acceptor(_io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), bind_port)) {

        _logger = LoggerManager::get_logger("sip0x.transport");
        _logger_siptrace = LoggerManager::get_logger("sip0x.siptrace");
        //asio::ip::tcp::resolver resolver(_io_service);
        //auto endpoint_iterator = resolver.resolve( { _bind_address, std::to_string(_bind_port) } );
      }

      virtual ~TransportLayer(void) {
        stop();

        delete _thread;
      }

      void set_listener(TransportListener* l)  { _listener  = l; }

      //! Start transport layer. 
      //! \returns true if transport layer was in
      void start(void) {
        if (_thread == nullptr) {
          _thread = new std::thread([this](){ process(); });
        }
      }

      //! Stop transport layer.
      //! \remark Returns in a synchronous way.
      void stop(void) {
        if (_thread != nullptr) {
          _thread_must_stop = true;
          if (_thread->joinable())_thread->join();
        }
      }

      void send(std::shared_ptr<SIPMessage> message, void* opaque_data) {
        std::string msg = message->to_string();
        std::shared_ptr<Connection> conn;

        LOG_INFO(_logger_siptrace, "Send\n----\n%s\n----", message->to_string().c_str());

        if (message->is_request) {
          /*
          The destination for the request is then computed. 
          Unless there is   local policy specifying otherwise, the destination 
          MUST be determined   by applying the DNS procedures described in [4] as follows.
          */

          // Impl: Local policy, proposed a callback to the application layer for proxy.

          // DNS procedures

          // Get Route-set and after that to the Request-URI

          /*
          If the   first element in the route set indicated a strict router (resulting   
          in forming the request as described in Section 12.2.1.1), the  
          procedures MUST be applied to the Request-URI of the request.   
          
          Otherwise, the procedures are applied to the first Route header field
          value in the request (if one exists), or to the request’s Request-URI
          if there is no Route header field present.  These procedures yield an 
          ordered set of address, port, and transports to attempt.  Independent
          of which URI is used as input to the procedures of [4], if the
          Request-URI specifies a SIPS resource, the UAC MUST follow the 
          procedures of [4] as if the input URI were a SIPS URI.
   Local policy MAY specify an alternate set of destinations to attempt. 
   If the Request-URI contains a SIPS URI, any alternate destinations   MUST be contacted with TLS.  Beyond that, there are no restrictions   on the alternate destinations if the request contains no Route header   field.  This provides a simple alternative to a pre-existing route   set as a way to specify an outbound proxy.  However, that approach   for configuring an outbound proxy is NOT RECOMMENDED; a pre-existing   route set with a single URI SHOULD be used instead.  If the request   contains a Route header field, the request SHOULD be sent to the   locations derived from its topmost value, but MAY be sent to any   server that the UA is certain will honor the Route and Request-URI   policies specified in this document (as opposed to those in RFC   2543).  In particular, a UAC configured with an outbound proxy SHOULD
   attempt to send the request to the location indicated in the first   Route header field value instead of adopting the policy of sending   all messages to the outbound proxy.
      This ensures that outbound proxies that do not add Record-Route      header field values will drop out of the path of subsequent      requests.  It allows endpoints that cannot resolve the first Route      URI to delegate that task to an outbound proxy.
   The UAC SHOULD follow the procedures defined in [4] for stateful   elements, trying each address until a server is contacted.  Each try   constitutes a new transaction, and therefore each carries a different   topmost Via header field value with a new branch parameter.   Furthermore, the transport value in the Via header field is set to   whatever transport was determined for the target server.
          
          */
          std::shared_ptr<SIPRequest> request = std::dynamic_pointer_cast<SIPRequest>(message);
          // Get destination from ReqeustURI.
          std::string host = request->uri.hostport.host;
          int port = request->uri.hostport.port;

          //host;
          conn = _connection_manager.get(0, port);
          if (conn != nullptr) {
            LOG_INFO(_logger, "Connection to %s:%d doesn't exists, trying to connect to remote host.", host, port);
            conn = connect(host, port);
          }
        }
        else {
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
                
                - Otherwise, if the Via header field value contains a "maddr"
                parameter, the response MUST be forwarded to the address listed
                there, using the port indicated in "sent-by", or port 5060 if
                none is present.  If the address is a multicast address, the
                response SHOULD be sent using the TTL indicated in the "ttl"
                parameter, or with a TTL of 1 if that parameter is not present.

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


          std::shared_ptr<SIPResponse> response = std::dynamic_pointer_cast<SIPResponse>(message);

          //response->
          // Get destination from ReqeustURI.
          //std::string host = request->uri.hostport.host;
          //int port = request->uri.hostport.port;
          // Check if for this destination is present a connection.
          // Try to connect.
          
          //conn = (Connection*)opaque_data;

        }
        // TODO: Revise this invokation!!!
        conn->async_write((unsigned char*)msg.c_str(), msg.length());
        // Fail-back on UDP.
      }


      //! Process network stuff.
      void process(void) {
        // TODO: logging
        std::cout << "Process thread started.\n";
        while (!_thread_must_stop) {
          // Install async operation.
          async_accept();
          // process async operation.
          _io_service.run();
        }
        std::cout << "Process thread ended.\n";
      }

      void async_accept(void) {
        _acceptor.async_accept(_tcp_socket, [this](std::error_code ec) {
          if (!ec) {
            _connection_manager.add(std::make_shared<Connection>(std::move(_tcp_socket), &_connection_manager, this));
          }
          async_accept();
        });
      }


      virtual void on_incoming_data(Connection* conn, uint8_t* buffer, std::size_t size) override {
        InputTokenStream iss(buffer, size);
        std::shared_ptr<sip0x::SIPMessage> message = parser.parse(iss);

        if (message != nullptr) {
          LOG_INFO(_logger_siptrace, "Recv\n----\n%s\n----", message->to_string().c_str());
        }

        if (message != nullptr && _listener != nullptr) {
          _listener->on_receive(message, conn); 
        }
      }

      std::shared_ptr<Connection> connect(std::string address, int port) {
        asio::ip::tcp::resolver resolver(_io_service);
        auto endpoint_iterator = resolver.resolve({ address, std::to_string(port) });

        std::shared_ptr<Connection> connection = std::make_shared<Connection>(std::move(_tcp_socket), nullptr, this);
        connection->connect(endpoint_iterator);
        _connection_manager.add(connection);
        return connection;
      }
    };
  }
}

#endif // SIP0X_LOGIC_UA_HPP__
