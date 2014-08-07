#include <thread>

#include "sip-0x.hpp"

int main(int argc, char* argv[]) {
  std::cout << "REGISTER client\n\n";

  Sip0x::Logic::Endpoint endpoint;

  //endpoint.register_to();


  //std::string address = "127.0.0.1";
  //std::string port = "5060";
  //if (argc >= 2) {
  //  address = argv[1];
  //}
  //if (argc >= 3) {
  //  port = argv[2];
  //}
  //
  //asio::io_service io_service;
  //
  //asio::ip::tcp::resolver resolver(io_service);
  //auto endpoint_iterator = resolver.resolve({ address, port });
  //
  //std::thread t([&io_service](){ while (1) { io_service.run(); } });
  //
  //Sip0x::Logic::UAC uac(io_service, "sip0x-uac");
  //
  //uac.connect(endpoint_iterator);
  //
  //t.join();

  return 0;
}
