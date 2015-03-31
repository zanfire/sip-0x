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

#include "UA.hpp"

namespace sip0x
{
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
    UAC(TransactionLayer* transaction, ApplicationDelegate* application_delegate, std::string domain, std::string useragent);
    virtual ~UAC(void);
    
    //! Handle a SIP request.
    void handle(std::shared_ptr<SIPRequest>& request);

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
    std::shared_ptr<SIPRequest> create_REQUEST(std::string const& callID, SIPURI request_URI, SIPMethod method);

    //! Create a REGISTER request for this UAC.
    std::shared_ptr<SIPRequest> create_REGISTER();

    //!
    //! Utils
    //!

    //! Generate a callID for this UAC.
    std::string generate_CallID(void);
    std::string generate_branch(void);
  };
}

#endif // SIP0X_LOGIC_UAC_HPP__
