#if !defined(SIP0X_PROTOCOL_SIPMESSAGE_HPP__)
#define SIP0X_PROTOCOL_SIPMESSAGE_HPP__

#include <string>
#include <vector>
#include <ostream>

#include "protocol/SIPURI.hpp"
#include "protocol/SIPMethod.hpp"
#include "protocol/SIPVersion.hpp"
#include "protocol/SIPMessageHeader.hpp"

namespace sip0x
{
  class SIPMessage {
  public:
    bool is_request = false;
    std::vector<std::shared_ptr<SIPMessageHeaderBase>> headers;
    std::vector<uint8_t> content;

    virtual std::string to_string(void) const {
      std::string out;
      for (auto h : headers) {
        out += h->to_string();
      }
      out += "\r\n";
      //for (auto c : content) {
      //  stream.put(c);
      //}
      return out;
    }

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
    std::shared_ptr<T> get_first(void) {
      // Search and returns the first occurrence.
      for (std::shared_ptr<SIPMessageHeaderBase> h : headers) {
        T* cast = dynamic_cast<T*>(h.get());
        if (cast != nullptr) {
          return std::dynamic_pointer_cast<T>(h);
        }
      }
      return nullptr;
    }

    std::string get_Via_branch() {
      std::shared_ptr<SIPMessageHeaderVia> via = get_first<SIPMessageHeaderVia>();
      if (via != nullptr) {
        for (auto param : via->params) {
          if (param.first.compare("branch") == 0) {
            return param.second;
          }
        }
      }
      return "";
    }
  };

  class SIPRequest : public SIPMessage {
  public:
    SIPMethod method;
    SIPURI uri;
    SIPVersion version;

    SIPRequest(void) : SIPMessage() {
      is_request = true;
    }

    virtual std::string to_string(void) const override {
      return sip0x::to_string(method) + ' ' + uri.to_string() + ' ' + version.to_string() + "\r\n" + SIPMessage::to_string(); 
    }
  };

  class SIPResponse : public SIPMessage {
  public:
    SIPVersion version;
    int status_code;
    std::string reason_phrase;

    SIPResponse(void) : SIPMessage() {
      is_request = false;
    }

    virtual std::string to_string(void) const override {
      return version.to_string() + ' ' + std::to_string(status_code) + ' ' + reason_phrase + "\r\n" + SIPMessage::to_string();
    }
  };
}

#endif // SIP0X_PROTOCOL_SIPMESSAGE_HPP__