#if !defined(SIP0X_PARSER_FACTORYCONTEXTSIPMESSAGE_HPP__)
#define SIP0X_PARSER_FACTORYCONTEXTSIPMESSAGE_HPP__

#include "parser/factory/FactoryContext.hpp"

#include <memory>

namespace sip0x
{
  namespace protocol {
    class SIPMessage;
  }
  namespace parser
  {
    class FactoryContextSIPMessage : public FactoryContext {
    protected:
      std::shared_ptr<protocol::SIPMessage> _message;
    public:
      virtual void create(std::string const& /*text*/) override;
     
      std::shared_ptr<protocol::SIPMessage> get_message(void) {
        return _message;
      }
    };
  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXTSIPMESSAGE_HPP__
