#if !defined(SIP0X_PROTOCOL_SIPMESSAGE_HPP__)
#define SIP0X_PROTOCOL_SIPMESSAGE_HPP__

#include <string>
#include <vector>
#include <ostream>
#include <memory>

#include "protocol/SIPURI.hpp"
#include "protocol/SIPMethod.hpp"
#include "protocol/SIPVersion.hpp"
#include "protocol/SIPMessageHeader.hpp"

namespace sip0x
{
  namespace protocol {
    class SIPMessage {
    public:
      bool is_request = false;
      std::vector<std::shared_ptr<SIPMessageHeaderBase>> headers;
      std::vector<uint8_t> content;

      SIPMessage(void) {}
      virtual ~SIPMessage(void) {}

      virtual std::string to_string(void) const;
      SIPMessage* clone(void) const;
      std::string get_Via_branch(void) const;

      //! Get or create an occurrence of given header line
      template<typename T>
      std::shared_ptr<SIPMessageHeaderBase> get_or_create(void) {
        // Search and returns the first occurrence.
        for (std::shared_ptr<SIPMessageHeaderBase> h : headers) {
          T* cast = dynamic_cast<T*>(h.get());
          if (cast != nullptr) {
            // Found
            return h;
          }
        }
        // Not found
        std::shared_ptr<T> header = std::make_shared<T>();
        headers.push_back(header);
        return header;
      }

      template<typename T>
      std::shared_ptr<T> get_first(void) const {
        // Search and returns the first occurrence.
        for (std::shared_ptr<SIPMessageHeaderBase> h : headers) {
          T* cast = dynamic_cast<T*>(h.get());
          if (cast != nullptr) {
            return std::dynamic_pointer_cast<T>(h);
          }
        }
        return nullptr;
      }

    protected:
      virtual SIPMessage* impl_clone(void) const = 0;
    };

    class SIPRequest : public SIPMessage {
    public:
      SIPMethod method;
      SIPURI uri;
      SIPVersion version;

      SIPRequest(void);
      virtual ~SIPRequest(void) {}

      virtual std::string to_string(void) const override;
    protected:
      virtual SIPMessage* impl_clone(void) const override;
    };

    class SIPResponse : public SIPMessage {
    public:
      SIPVersion version;
      int status_code;
      std::string reason_phrase;

      SIPResponse(void);
      virtual ~SIPResponse(void) {}

      bool is_provisional(void) const     { return status_code >= 100 && status_code <= 199; }
      bool is_success(void) const         { return status_code >= 200 && status_code <= 299; }
      bool is_redirection(void) const     { return status_code >= 300 && status_code <= 399; }
      bool is_client_error(void) const    { return status_code >= 400 && status_code <= 499; }
      bool is_server_error(void) const    { return status_code >= 500 && status_code <= 599; }
      bool is_global_failure(void) const  { return status_code >= 600 && status_code <= 699; }

      virtual std::string to_string(void) const override;
    protected:
      virtual SIPMessage* impl_clone(void) const override;
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPMESSAGE_HPP__