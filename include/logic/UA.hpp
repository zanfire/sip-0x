#if !defined(SIP0X_LOGIC_UA_HPP__)
#define SIP0X_LOGIC_UA_HPP__

#include "asio_header.hpp"

#include <string>
#include <memory>

#include "logic/ApplicationDelegate.hpp"
#include "logic/TransactionLayer.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"

namespace sip0x
{
  namespace Logic
  {
    class UAListener {
    public:
      // success
      virtual void on_request(std::shared_ptr<Transaction>& tran, std::shared_ptr<SIPRequest>& request) {}
      virtual void on_response(std::shared_ptr<Transaction>& tran, std::shared_ptr<SIPResponse>& response) = 0;
    };

    using namespace sip0x::Utils::Log;

    /// Implement basic logic of a SIP User-Agent.
    class UA {
    protected:
      std::shared_ptr<Logger> _logger;
      std::set<UAListener*> _listeners;
      // Is it really needed??
      ApplicationDelegate* _application_delegate;

      TransactionLayer* _transaction = nullptr;
      // SIP
      std::string _domain;
      std::string _useragent;

    public:
      UA(ApplicationDelegate* application_delegate, TransactionLayer* transaction, std::string domain, std::string useragent) :
        _application_delegate(application_delegate),
        _transaction(transaction),
        _domain(domain),
        _useragent(useragent) {

      }

      virtual ~UA(void) {
      }

      void add_listener(UAListener* listener) {
        _listeners.insert(listener);
      }

      void remove_listener(UAListener* listener) {
        _listeners.erase(listener);
      }

    protected:

      void raise_listener(std::shared_ptr<Transaction>& tran, std::shared_ptr<SIPResponse>& response) {
        for (auto listener : _listeners) {
          listener->on_response(tran, response);
        }
      }


      //! \brief Add default header line. Ex: User agent, Max-Forwards, Via etc
      void add_default_header_lines(SIPMessage* message) {
        // Max-Forwards: 70
        std::shared_ptr<SIPMessageHeaderMax_Forwards> max_forward = std::make_shared<SIPMessageHeaderMax_Forwards>();
        max_forward->max = 70;
        message->headers.push_back(max_forward);

        std::shared_ptr<SIPMessageHeaderUser_Agent> user_agent = std::make_shared<SIPMessageHeaderUser_Agent>();
        user_agent->user_agent = _useragent;
        message->headers.push_back(user_agent);
      }

      void add_header_cseq(SIPMessage* message, SIPMethod method, int seq) {
        std::shared_ptr<SIPMessageHeaderCSeq> cseq = std::make_shared<SIPMessageHeaderCSeq>();
        cseq->seq = seq;
        cseq->method = method;

        message->headers.push_back(cseq);
      }

      void add_header_call_ID(SIPMessage* message, std::string const& callID) {
        std::shared_ptr<SIPMessageHeaderCall_ID> call_ID = std::make_shared<SIPMessageHeaderCall_ID>();
        call_ID->callID = callID;
        message->headers.push_back(call_ID);
      }

      void add_header_via(SIPMessage* message, char const* transport, char const* branch) {
        // Via: SIP/2.0/UDP bobspc.biloxi.com:5060;branch=z9hG4bKnashds7
        std::shared_ptr<SIPMessageHeaderVia> via = std::make_shared<SIPMessageHeaderVia>();
        via->protocol = "SIP";
        via->version = "2.0";
        via->transport = transport; // TODO: Should be updated by the transport layer.
        via->hostport.host = _domain; // It should be the nat or local IP.
        via->params.push_back(std::make_pair("branch", branch)); // TODO: Implement a create branch.
        message->headers.push_back(via);

      }

      void add_content(SIPMessage* message, uint8_t* content, std::size_t size) {
        // Content-Length: 0
        std::shared_ptr<SIPMessageHeaderContent_Length> content_length = std::make_shared<SIPMessageHeaderContent_Length>();
        content_length->length = size;
        message->headers.push_back(content_length);
        
        if (content != nullptr) {
          // TODO: Implements.
          //message->content = nullptr;
        }
      }
    };
  }
}

#endif // SIP0X_LOGIC_UA_HPP__
