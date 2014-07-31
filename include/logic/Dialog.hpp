#if !defined(SIP0X_LOGIC_DIALOG_HPP__)
#define SIP0X_LOGIC_DIALOG_HPP__

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

    class Dialog;

    class DialogListener {
    };

    /// Implement basic logic for SIP Dialog.
    class Dialog {
    protected:
      std::shared_ptr<Logger> _logger;

    public:
      Dialog(void) {
        _logger = LoggerManager::get_logger("Sip0x.Logic.Dialog");
      }

      virtual ~Dialog(void) {
      }
    }
  }
}

#endif // SIP0X_LOGIC_DIALOG_HPP__
