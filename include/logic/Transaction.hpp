#if !defined(SIP0X_LOGIC_TRANSACTION_HPP__)
#define SIP0X_LOGIC_TRANSACTION_HPP__

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

    class Transaction;

    class TransactionListener {
      virtual void onCreated(Transaction* tran, SIPRequest* request) = 0;
      virtual void onTimedout(Transaction* tran) = 0;
      virtual void onCompleted(Transaction* tran, SIPResponse* response) = 0;
    };

    /// Implement basic logic for SIP Transaction.
    class Transaction {
    protected:
      std::shared_ptr<Logger> _logger;

      SIPRequest* _request;
      SIPResponse* _response;

    public:
      Transaction(SIPRequest* request, SIPResponse* response) : _request(request), _response(response) {
        _logger = LoggerManager::get_logger("Sip0x.Logic.Transaction");
      }

      virtual ~Transaction(void) {
      }
    };
  }
}

#endif // SIP0X_LOGIC_UAS_HPP__
