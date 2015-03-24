#if !defined(SIP0X_LOGIC_DIALOG_HPP__)
#define SIP0X_LOGIC_DIALOG_HPP__

#include "protocol/SIP.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"
#include "utils/InputTokenStream.hpp"

namespace sip0x
{
  namespace Logic
  {
    using namespace sip0x::utils;
    using namespace sip0x;

    class Dialog;

    class DialogListener {
    };

    /// Implement basic logic for SIP Dialog.
    class Dialog {
    protected:
      std::shared_ptr<Logger> _logger;

    public:
      Dialog(void) {
        _logger = LoggerFactory::get_logger("sip0x.Logic.Dialog");
      }

      virtual ~Dialog(void) {
      }
    }
  }
}

#endif // SIP0X_LOGIC_DIALOG_HPP__
