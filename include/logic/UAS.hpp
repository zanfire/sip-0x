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
    class UAS : TransactionListener {
    protected:
      std::shared_ptr<Logger> _logger;
      TransactionLayer _transaction_layer;
      
    public:
      UAS(TransportLayer* transport) : TransactionListener(), _transaction_layer(this, transport, true)  {
        _logger = LoggerManager::get_logger("sip0x.Logic.UAS");
      }

      virtual ~UAS(void) {
      }

      virtual void on_trying(Transaction* tran) override {
        SIPRequest* request = tran->request.get();

        switch (request->method) {
          case SIPMethod::SIPMETHOD_REGISTER:
          {
            process_REGISTER(request);
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

      void process_REGISTER(SIPRequest* request) {
        // TODO: process and notify the Application of the register method.

        // Ask to the application layer if accept register from client


      }

    };
  }
}

#endif // SIP0X_LOGIC_UAS_HPP__
