#if !defined(SIP0X_LOGIC_UAC_HPP__)
#define SIP0X_LOGIC_UAC_HPP__

//!
//! Copyright 2014 Matteo Valdina
//!
//! Licensed under the Apache License, Version 2.0 (the "License");
//! you may not use this file except in compliance with the License.
//! You may obtain a copy of the License at
//!
//!     http://www.apache.org/licenses/LICENSE-2.0
//!
//! Unless required by applicable law or agreed to in writing, software
//! distributed under the License is distributed on an "AS IS" BASIS,
//! WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//! See the License for the specific language governing permissions and
//! limitations under the License.
//!

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

#include "logic/UA.hpp"
#include "logic/Transaction.hpp"
#include "logic/TransactionLayer.hpp"
#include "logic/TransportLayer.hpp"
#include "protocol/SIP.hpp"

#include <random>

namespace sip0x
{
  namespace Logic
  {
    using namespace sip0x::utils;

    //!
    //! \brief Models a SIP UAC (User Agent Client). 
    //! 
    //! A UAC is in charge of generate a SIP request.
    //! 
    //! \author Matteo Valdina  
    //!
    class UAC : public UA, TransactionLayerResponseListener {
    protected:
      std::default_random_engine _random_engine;
      std::uniform_int_distribution<int> _uniform_dist_Az;

    public:
        UAC(TransactionLayer* transaction, ApplicationDelegate* application_delegate, std::string domain, std::string useragent) 
          : UA(application_delegate, transaction, domain, useragent),
            TransactionLayerResponseListener(),
            _uniform_dist_Az('A', 'z') {

          // Seed with a real random value, if available
          std::random_device rd;
          _random_engine = std::default_random_engine(rd());

          _transaction->set_listener_response(this);
      }


      virtual ~UAC(void) {
      }

      //! Handle a SIP request.
      void handle(std::shared_ptr<SIPRequest>& request) {
        _transaction->process_request(request, false, nullptr);
      }

      //!
      //! Transaction listener impl.
      //!

      virtual void on_incoming_response(std::shared_ptr<Transaction>& tran, std::shared_ptr<SIPResponse>& response) override {
        raise_listener(tran, response);
      }

      //!
      //! Request creation.
      //!

      //! Create a generic REQUEST for this UAC.
      std::shared_ptr<SIPRequest> create_REQUEST(std::string const& callID, SIPURI request_URI, SIPMethod method) {
        std::shared_ptr<SIPRequest> request = std::make_shared<SIPRequest>();
        request->method = method;
        request->version.major = 2;
        request->uri = request_URI;

        // Via: SIP/2.0/UDP bobspc.biloxi.com:5060;branch=z9hG4bKnashds7
        add_header_via(request.get(), "TCP", generate_branch().c_str());
        add_default_header_lines(request.get());
        add_header_cseq(request.get(), method, 1);
        add_header_call_ID(request.get(), callID);
        add_content(request.get(), nullptr, 0);

        return request;
      }

      //! Create a REGISTER request for this UAC.
      std::shared_ptr<SIPRequest> create_REGISTER() {
        std::string callID = generate_CallID();
        SIPURI requestURI;
        requestURI.hostport.host = "requestURI@todo"; // TODO: Provide a parsing method for on the fly request.
        std::shared_ptr<SIPRequest> request = create_REQUEST(callID, requestURI, SIPMethod::SIPMETHOD_REGISTER);

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

        // Add Expires header entry.
        // NOTO: Currently we place an header entry but we can update the Contact.
        std::shared_ptr<SIPMessageHeaderExpires> expires = std::make_shared<SIPMessageHeaderExpires>();
        expires->expires = 3;
        request->headers.push_back(expires);
        return request;
      }

      //!
      //! Utils
      //!

      //! Generate a callID for this UAC.
      std::string generate_CallID(void) {
        char buffer[16];

        buffer[sizeof(buffer) - 1] = 0x00;
        int idx = 0;
        while (idx < (sizeof(buffer) - 1)) {
          int value = _uniform_dist_Az(_random_engine);
          // Accept this value
          if ((value >= 'A' && value <= 'Z') || (value >= '0' && value <= '9') || (value >= 'a' && value <= 'z')) {
            buffer[idx] = (char)value;
            idx++;
          }
        }

        if (_domain.empty()) {
          return std::string(buffer);
        }
        else {
          return std::string(buffer) + '@' + _domain;
        }
      }
   
      std::string generate_branch(void) {
        char buffer[32];

        buffer[sizeof(buffer) - 1] = 0x00;
        int idx = 0;
        while (idx < (sizeof(buffer) - 1)) {
          int value = _uniform_dist_Az(_random_engine);
          // Accept this value
          if ((value >= 'A' && value <= 'Z') || (value >= '0' && value <= '9') || (value >= 'a' && value <= 'z')) {
            buffer[idx] = (char)value;
            idx++;
          }
        }

        return "z9hG4bK_" + std::string(buffer);
      }
    };

  }
}

#endif // SIP0X_LOGIC_UAC_HPP__
