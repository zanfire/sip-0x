
#include "logic\UAS.hpp"


int main(int argc, char* argv[])
{
  try
  {
    asio::io_service io_service;
    Sip0x::Logic::UAS uas("sip0x-uas", io_service, 5060);

    uas.process();
    //
    //
    //
    //server s(io_service, std::atoi(argv[1]));
    //
    //io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
