#if !defined(SIP0X_LOGIC_UAS_HPP__)
#define SIP0X_LOGIC_UAS_HPP__

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

#include "logic/TransportListener.hpp"
#include "logic/UA.hpp"

namespace sip0x
{
  namespace Logic
  {
    using namespace sip0x::Utils::Log;

    //!
    //! \brief Models a SIP UAS (User Agent Server). 
    //! 
    //! \author Matteo Valdina  
    //! 
    class UAS : public TransactionListener, public UA {
    protected:
      TransactionLayer _transaction_layer;
      
    public:
      UAS(TransportLayer* transport, ApplicationDelegate* application_delegate, std::string domain, std::string useragent) :
        TransactionListener(), 
        UA(application_delegate, domain, useragent),
        _transaction_layer(this, transport, true)  {
        _logger = LoggerManager::get_logger("sip0x.Logic.UAS");
      }

      virtual ~UAS(void) {
      }

      virtual void on_trying(Transaction* tran) override {
        std::shared_ptr<SIPRequest>& request = tran->request;

        switch (request->method) {
          case SIPMethod::SIPMETHOD_REGISTER:
          {
            process_REGISTER(tran);
            break;
          }

        }
      }

      virtual void on_processing(Transaction* tran) override {

      }

      virtual void on_completed(Transaction* tran) override {

      }

      virtual void on_terminated(Transaction* tran) override {

      }

    private:

      void process_REGISTER(Transaction* transaction) {
        // TODO: process and notify the Application of the register method.

        // Ask to the application layer if accept register from client

        bool accepted = _application_delegate->raise_cb_registrar_update(transaction->request);
        if (accepted) {
          // Create a valid response.
          std::shared_ptr<SIPResponse> response = create_RESPONSE_for(transaction->request.get(), 200, "OK");
          _transaction_layer.process_response(response, false, transaction->opaque_data);
        }
        else {
          // Create an reject response
        }
      }


      std::shared_ptr<SIPResponse> create_RESPONSE_for(SIPRequest* request, int code, char const* phrase) {
        std::shared_ptr<SIPResponse> response = std::make_shared<SIPResponse>();
        response->status_code = code;
        response->reason_phrase = phrase;
        response->version.major = 2;
        
        add_default_header_lines(response.get());
        std::shared_ptr<SIPMessageHeaderCall_ID> callID = request->get_first<SIPMessageHeaderCall_ID>();
        response->headers.push_back(callID);
        
        add_header_via(response.get(), "TCP", request->get_Via_branch().c_str());
        add_header_cseq(response.get(), request->method, 1);


        return response;
      }
    };
  }
}

#endif // SIP0X_LOGIC_UAS_HPP__
