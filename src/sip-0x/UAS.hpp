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

#include "listeners/TransactionListener.hpp"
#include "UA.hpp"

#include <string>

namespace sip0x
{
  //!
  //! \brief Models a SIP UAS (User Agent Server). 
  //! 
  //! \author Matteo Valdina  
  //! 
  class UAS : public UA, listeners::TransactionLayerRequestListener {
  protected:
      
  public:
    UAS(TransactionLayer* transaction, ApplicationDelegate* application_delegate, std::string domain, std::string useragent);
    virtual ~UAS(void);

    virtual void on_incoming_request(std::shared_ptr<Transaction>& tran, std::shared_ptr<protocol::SIPRequest>& request) override;


  private:

    void process_REGISTER(std::shared_ptr<Transaction>& transaction);
    std::shared_ptr<protocol::SIPResponse> create_RESPONSE_for(protocol::SIPRequest* request, int code, char const* phrase);
  };
}

#endif // SIP0X_LOGIC_UAS_HPP__
