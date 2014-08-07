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

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"

#include "protocol/SIP.hpp"

namespace Sip0x
{
  namespace Logic
  {
    using namespace Sip0x::Utils::Log;

    //!
    //! \brief Models a SIP UAC (User Agent Client). 
    //! 
    //! A UAC is in charge of generate a SIP request.
    //! 
    //! \author Matteo Valdina  
    //!
    class UAC {
    protected:
      std::string _address;
    public:
      UAC(void) {
      }

      virtual ~UAC(void) {
      }

      //!
      //! Request creation.
      //!

      //! Create a generic REQUEST for this UAC.
      std::unique_ptr<SIPRequest> create_REQUEST(std::string const& callID, SIPURI request_URI, SIPMethod method) {
        std::unique_ptr<SIPRequest> request = std::make_unique<SIPRequest>();
        request->method = method;
        request->version.major = 2;
        request->uri = request_URI;

        // Via: SIP/2.0/UDP bobspc.biloxi.com:5060;branch=z9hG4bKnashds7
        std::shared_ptr<SIPMessageHeaderVia> via = std::make_shared<SIPMessageHeaderVia>();
        via->protocol = "SIP";
        via->version = "2.0";
        via->transport = "TCP"; // TODO: Should be updated by the transport layer.
        via->hostport.host = _address; // TODO: Check this value
        via->params.push_back(std::make_pair("branch", "z9hG4bKnashds7")); // TODO: Implement a create branch.
        request->headers.push_back(via);

        // Max-Forwards: 70
        std::shared_ptr<SIPMessageHeaderMax_Forwards> max_forward = std::make_shared<SIPMessageHeaderMax_Forwards>();
        max_forward->max = 70;
        request->headers.push_back(max_forward);
        std::shared_ptr<SIPMessageHeaderCall_ID> call_ID = std::make_shared<SIPMessageHeaderCall_ID>();
        call_ID->callID = callID;
        request->headers.push_back(call_ID);

        std::shared_ptr<SIPMessageHeaderCSeq> cseq = std::make_shared<SIPMessageHeaderCSeq>();
        cseq->seq = 1;
        cseq->method = method;

        // Content-Length: 0
        std::shared_ptr<SIPMessageHeaderContent_Length> content_length = std::make_shared<SIPMessageHeaderContent_Length>();
        content_length->length = 0;
        request->headers.push_back(content_length);

        return request;
      }

      //! Create a REGISTER request for this UAC.
      std::unique_ptr<SIPRequest> create_REGISTER() {
        std::string callID = generate_CallID();
        SIPURI requestURI;
        requestURI.hostport.host = "requestURI@todo"; // TODO: Provide a parsing method for on the fly request.
        std::unique_ptr<SIPRequest> request = create_REQUEST(callID, requestURI, SIPMethod::SIPMETHOD_REGISTER);
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
        
        // Add Expires header entry.
        // NOTO: Currently we place an hader entry but we can update the Contact.
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
        // TODO: Implements.
        return "dfsf-123fsf-423-f-sf-r4-3444@sip0x";
      }
    };
  }
}

#endif // SIP0X_LOGIC_UAC_HPP__
