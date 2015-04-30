#include "Endpoint.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

#include "parser/Parser.hpp"

#include "RegisterClient.hpp"
#include "UAC.hpp"
#include "UAS.hpp"
#include "TransportLayer.hpp"
#include "TransactionLayer.hpp"
#include "ApplicationDelegate.hpp"

#include <set>
#include <thread>
#include <condition_variable>


using namespace sip0x;
using namespace sip0x::utils;


Endpoint::Endpoint(void) {
  _logger = LoggerFactory::get_logger("sip0x.Endpoint");
  LOG_DEBUG(_logger, "Endpoint ctor.");
}


Endpoint::~Endpoint(void) {
  LOG_DEBUG(_logger, "Endpoint dtor.");
}


bool Endpoint::initialize(Endpoint::EndpointConfig const& configuration) {
  if (_initialized) {
    LOG_WARN(_logger, "Skipping initialization because Endpoint was initialized.");
    return false;
  }
  // Pre-load SIP grammar.
  parser::Parser::load_grammar();

  // Initialize transport layer.
  _transport = TransportLayer::create(configuration.bind_address, configuration.bind_port);
  _transport->start();
  // Initialize transaction layer
  _transaction = new TransactionLayer(_transport);
  // Initialize User agents
  _uac = new UAC(_transaction, this, configuration.domainname, "sip0x-ua");
  _uas = new UAS(_transaction, this, configuration.domainname, "sip0x-ua");

  _thread = new std::thread(&Endpoint::process, this);

  _initialized = true;
  LOG_INFO(_logger, "Endpoint initialized.");
  return true;
}


bool Endpoint::unitialize(void) {
  // TODO: Unregister RegisterClients.

  delete _thread;
  _thread = nullptr;
  // TODO: delete UAC and move to the right place.
  delete _uac;
  _uac = nullptr;

  _initialized = false;
  return true;
}

//! Register endpoint to a remote server
//! \arg remote_server address of the remote server.
//! \arg remote_port remote port.
//! \arg refresh_timeout_secs is desired refresh timeout in seconds.
void Endpoint::register_to(std::string contact, std::string remote_server, int remote_port, uint32_t refresh_timeout_secs) {
  LOG_DEBUG(_logger, "Endpoint (contact: %s) will register to %s:%d each %u seconds.", contact.c_str(), remote_server.c_str(), remote_port, refresh_timeout_secs);
  // Create a register client and start processing.
  std::shared_ptr<RegisterClient> regclient = RegisterClient::create(_uac, remote_server, remote_port);
  regclient->set_desired_expires(refresh_timeout_secs);
  regclient->start();
        
  _mtx.lock();
  _register_clients.insert(regclient);
  _mtx.unlock();
}


std::string Endpoint::describe_status() {
  std::string out;
  out += "Initialized: ";
  if (_initialized) {
    out += "true";
  }
  else {
    out += "false";
  }
  for (auto r : _register_clients) {
    out += ", register client: " + r->describe_status();
  }
  return out;
}


void Endpoint::process(void) {
  LOG_INFO(_logger, "Processing thread started.");
  // Min resolution.
  std::chrono::milliseconds ms(_thread_min_resolution_ms);
  while (!_thread_must_stop) {
    _mtx.lock();
    // Handle registration.
    for (auto reg : _register_clients) {
      reg->on_process();
    }
    // Handle UAC?
    // Handle UAS?
    _mtx.unlock();

    std::this_thread::sleep_for(ms); // TODO: Implement with a cond_var.
  }
  LOG_INFO(_logger, "Processing thread terminated.");
}
