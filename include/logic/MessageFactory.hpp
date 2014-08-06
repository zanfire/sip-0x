#if !defined(SIP0X_LOGIC_MESSAGEFACTORY_HPP__)
#define SIP0X_LOGIC_MESSAGEFACTORY_HPP__

#include "protocol/SIP.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"
#include "utils/InputTokenStream.hpp"

namespace Sip0x
{
  namespace Logic
  {
    using namespace Sip0x::Utils::Log;
    using namespace Sip0x::Protocol;

    //! Returns first occurrence of type T. If is not present in header vector it will be added.
    template<typename T>
    static std::shared_ptr<T> get_or_set_first_occurrence(SIPMessage* message) {
      // Search and returns the first occurrence.
      for (auto h : message->headers) {
        T* cast = dynamic_cast<T*>(h.get());
        if (cast != nullptr) {
          // Found
          return h;
        }
      }
      // Not found
      std::shared_ptr<T> header = std::make_shared<T>();
      message->headers.push_back(header);
      return header;
    }

    template<typename T>
    static std::shared_ptr<T> get_first_occurrence(SIPMessage* message) {
      // Search and returns the first occurrence.
      for (auto h : message->headers) {
        T* cast = dynamic_cast<T*>(h.get());
        if (cast != nullptr) {
          // Found
          return cast
        }
      }
      return nullptr;
    }

    static std::unique_ptr<SIPRequest> create_REQUEST(std::string const& callID, HostPort send_by) {
      std::unique_ptr<SIPRequest> request = std::make_unique<SIPRequest>();
      request->method = SIPMethod::SIPMETHOD_extension;
      request->version.major = 2;

      // Via: SIP/2.0/UDP bobspc.biloxi.com:5060;branch=z9hG4bKnashds7
      std::shared_ptr<SIPMessageHeaderVia> via = std::make_shared<SIPMessageHeaderVia>();
      via->protocol = "SIP";
      via->version = "2.0";
      via->transport = "TCP";
      via->hostport = send_by;
      via->params.push_back(std::make_pair("branch", "z9hG4bKnashds7"));
      request->headers.push_back(via);

      // Max-Forwards: 70
      std::shared_ptr<SIPMessageHeaderMax_Forwards> max_forward = std::make_shared<SIPMessageHeaderMax_Forwards>();
      max_forward->max = 70;
      request->headers.push_back(max_forward);
      // Call-ID: 843817637684230@998sdasdh09 
      std::shared_ptr<SIPMessageHeaderCall_ID> call_ID = std::make_shared<SIPMessageHeaderCall_ID>();
      call_ID->callID = callID;
      request->headers.push_back(call_ID);

      // Content-Length: 0
      std::shared_ptr<SIPMessageHeaderContent_Length> content_length = std::make_shared<SIPMessageHeaderContent_Length>();
      content_length->length = 0;
      request->headers.push_back(content_length);

      return request;
    }

    static void set_REGISTER(std::unique_ptr<SIPRequest>& request, unsigned long exp) {
      /*
      REGISTER sip:registrar.biloxi.com SIP/2.0
      Via: SIP/2.0/UDP bobspc.biloxi.com:5060;branch=z9hG4bKnashds7
      Max-Forwards: 70       
      To: Bob <sip:bob@biloxi.com>       
      Call-ID: 843817637684230@998sdasdh09 
      From: Bob <sip:bob@biloxi.com>;tag=456248       
      CSeq: 1826 REGISTER       
      Contact: <sip:bob@192.0.2.4> 
      Expires: 7200       
      Content-Length: 0
      */
      request->method = SIPMethod::SIPMETHOD_REGISTER;
      // CSeq
      auto cseq = get_or_set_first_occurrence<SIPMessageHeaderCSeq>(request.get());
      cseq->seq = 1;
      cseq->method = SIPMethod::SIPMETHOD_REGISTER;
      // Expires
      auto expires = get_or_set_first_occurrence<SIPMessageHeaderExpires>(request.get());
      expires->expires = exp;
    }
  }
}

#endif // SIP0X_LOGIC_MESSAGEFACTORY_HPP__
