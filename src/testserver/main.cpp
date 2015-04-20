#include "utils\Logger.hpp"
#include "utils\LoggerFactory.hpp"
#include "Endpoint.hpp"

#include <thread>
#include <string>
#include <memory>

int main(int argc, char* argv[]) {
  sip0x::utils::LoggerFactory* loggermanager = sip0x::utils::LoggerFactory::get_instance();
  loggermanager->configure("..\\..\\..\\docs\\logger.ini");

  std::cout << "SIP server\n\n";

  sip0x::Endpoint endpoint;
  // Callbacks.
  endpoint.set_cb_registrar_update([](std::shared_ptr<sip0x::protocol::SIPRequest>&) { return true; });
  endpoint.set_cb_registrar_get_expires([](std::shared_ptr<sip0x::protocol::SIPRequest>&) { return 30; });
  // Configuration.
  sip0x::Endpoint::EndpointConfig config;
  config.bind_address = "127.0.0.1";
  config.bind_port = 5060;
  config.username = "server";
  config.domainname = "127.0.0.1";

  // Initialize.
  endpoint.initialize(config);
  
  std::chrono::milliseconds ms(30000);
  // Never ending loops.
  while (true) {
    std::cout << "Status: " << endpoint.describe_status() << '\n';
    std::this_thread::sleep_for(ms);
  }
  return 0;
}
