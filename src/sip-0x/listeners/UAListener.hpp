#if !defined(SIP0X_LOGIC_UALISTENER_HPP__)
#define SIP0X_LOGIC_UALISTENER_HPP__

#include <memory>

namespace sip0x
{
  class Transaction;
  
  namespace Protocol {
    class SIPRequest;
    class SIPResponse;
  }

  class UAListener {
  public:
    virtual void on_request(std::shared_ptr<Transaction>& tran, std::shared_ptr<Protocol::SIPRequest>& request) {}
    virtual void on_response(std::shared_ptr<Transaction>& tran, std::shared_ptr<Protocol::SIPResponse>& response) {};
  };
}

#endif // SIP0X_LOGIC_UALISTENER_HPP__
