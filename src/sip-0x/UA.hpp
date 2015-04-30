#if !defined(SIP0X_LOGIC_UA_HPP__)
#define SIP0X_LOGIC_UA_HPP__

#include <string>
#include <memory>
#include <set>

#include "protocol/SIPMethod.hpp"

namespace sip0x
{
  namespace utils {
    class Logger;
  }

  namespace protocol {
    class SIPMessage;
    class SIPRequest;
    class SIPResponse;
  }

  namespace listeners {
    class UAListener;
  }

  class ApplicationDelegate;
  class Transaction;
  class TransactionLayer;
  class TransportLayer;

  //! Provide common logic implementation for User-Agent Server and Client.
  //! 
  //! Server and client specific implementations are provided by the derived
  //! classes UAS and UAC.
  class UA {
  protected:
    std::shared_ptr<utils::Logger> _logger;
    std::set<std::shared_ptr<listeners::UAListener>> _listeners;
    // Is it really needed??
    ApplicationDelegate* _application_delegate;

    TransactionLayer* _transaction = nullptr;
    // SIP
    std::string _domain;
    std::string _useragent;

  public:
    UA(ApplicationDelegate* application_delegate, TransactionLayer* transaction, std::string domain, std::string useragent);
    virtual ~UA(void);

    void add_listener(std::shared_ptr<listeners::UAListener>& listener);
    void remove_listener(std::shared_ptr<listeners::UAListener>& listener);
  protected:

    void raise_listener(std::shared_ptr<Transaction>& tran, std::shared_ptr<protocol::SIPResponse const>& response);

    //! \brief Add default header line. Ex: User agent, Max-Forwards, Via etc
    void add_default_header_lines(protocol::SIPMessage* message);
    void add_header_cseq(protocol::SIPMessage* message, protocol::SIPMethod method, int seq);
    void add_header_expires(protocol::SIPMessage* message, int expires);
    void add_header_call_ID(protocol::SIPMessage* message, std::string const& callID);
    void add_header_via(protocol::SIPMessage* message, char const* transport, char const* branch);
    void add_content(protocol::SIPMessage* message, uint8_t* content, std::size_t size);
  };
}

#endif // SIP0X_LOGIC_UA_HPP__
