#if !defined(SIP0X_LOGIC_UALISTENER_HPP__)
#define SIP0X_LOGIC_UALISTENER_HPP__

#include <memory>

namespace sip0x
{
  class Transaction;
  
  namespace protocol {
    class SIPRequest;
    class SIPResponse;
  }

  namespace listeners {

    class UAListener {
    public:
      virtual void on_request(std::shared_ptr<sip0x::Transaction>& tran, std::shared_ptr<sip0x::protocol::SIPRequest const>& request) {}
      virtual void on_response(std::shared_ptr<sip0x::Transaction>& tran, std::shared_ptr<sip0x::protocol::SIPResponse const>& response) {};
    };
  }
}

#endif // SIP0X_LOGIC_UALISTENER_HPP__
