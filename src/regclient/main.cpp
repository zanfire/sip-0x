#include <thread>

#include "utils\Logger.hpp"
#include "utils\LoggerFactory.hpp"
#include "Endpoint.hpp"

int main(int argc, char* argv[]) {
  sip0x::utils::LoggerFactory* loggermanager = sip0x::utils::LoggerFactory::get_instance();
  loggermanager->configure("..\\..\\..\\docs\\logger.ini");

  std::cout << "REGISTER client\n\n";

  // Give a configuration to this params.
  std::string registrar_server = "127.0.0.1";
  int registrar_port = 5060;

  sip0x::Endpoint endpoint;
  
  sip0x::Endpoint::EndpointConfig config;

  config.bind_address = "127.0.0.1";
  config.bind_port = 55060;
  config.username = "client";
  config.domainname = "127.0.0.1";
  
  // Initialize.
  endpoint.initialize(config);
  endpoint.register_to("regclient_1", registrar_server, registrar_port, 3600);

  std::chrono::milliseconds ms(3000);
  // Never ending loops.
  while (true) {
    std::cout << "Status: " << endpoint.describe_status() << '\n';
    std::this_thread::sleep_for(ms);
  }
  return 0;
}
