#if !defined(SIP0X_REMOTEPEER_HPP__)
#define SIP0X_REMOTEPEER_HPP__

#include <string>
#include <memory>

#include "utils/Connection.hpp"

namespace sip0x
{
  //! Abstraction that represents the remote peer.
  class RemotePeer  {
  };

  class RemotePeerTCP : public RemotePeer {
  public:
    std::shared_ptr<utils::Connection> connection;
  };
}

#endif // SIP0X_REMOTEPEER_HPP__
