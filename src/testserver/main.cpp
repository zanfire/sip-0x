#include <thread>

#include "sip-0x.hpp"

int main(int argc, char* argv[]) {
  std::cout << "SIP server\n\n";
;

  Sip0x::Logic::Endpoint endpoint;

  Sip0x::Logic::Endpoint::EndpointConfig config;

  config.bind_address = "127.0.0.1";
  config.bind_port = 5060;
  config.username = "server";
  config.domainname = "127.0.0.1";

  // Initialize.
  endpoint.initialize(config);
  
  std::chrono::milliseconds ms(3000);
  // Never ending loops.
  while (true) {
    std::cout << "Status: " << endpoint.describe_status() << '\n';
    std::this_thread::sleep_for(ms);
  }
  return 0;
}
