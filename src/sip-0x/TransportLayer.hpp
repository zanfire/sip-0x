#if !defined(SIP0X_LOGIC_TRANSPORTLAYER_HPP__)
#define SIP0X_LOGIC_TRANSPORTLAYER_HPP__

#include <string>
#include <memory>
#include <thread>

namespace sip0x
{
  using namespace sip0x::utils;

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
    TransportLayer(std::string const& bind_address, int const& bind_port);

    virtual ~TransportLayer(void);

    void set_listener(TransportListener* l)  { _listener  = l; }

    //! Start transport layer. 
    //! \returns true if transport layer was in
    void start(void);

    //! Stop transport layer.
    //! \remark Returns in a synchronous way.
    void stop(void);
    void send(std::shared_ptr<Transaction>& trnasaction, std::shared_ptr<SIPMessage> const& message) {
    //! Process network stuff.
    void process(void) {
    void async_accept(void) {
    virtual void on_incoming_data(Connection* conn, uint8_t* buffer, std::size_t size) override {
    std::shared_ptr<Connection> connect(std::string address, int port) {
    uint32_t resolve(std::string address) {
  };
}

#endif // SIP0X_LOGIC_UA_HPP__
