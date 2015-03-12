#if !defined(SIP0X_PARSER_SIPPARSER_HPP__)
#define SIP0X_PARSER_SIPPARSER_HPP__

#include <vector>
#include <sstream>
#include <iostream>
#include <memory>

#include "parser/base/TokenAbstract.hpp"
#include "parser/sip/TokenSIPMessage.hpp"
#include "parser/factory/FactoryContext.hpp"
#include "parser/Parser.hpp"

#include "utils/Logger.hpp"
#include "utils/LoggerFactory.hpp"

#include "protocol/SIPMessage.hpp"

namespace sip0x
{
  namespace Parser
  {
    using namespace sip0x::Utils;

    class SIPParser {
    private:
      TokenSIPMessage grammar;

    public:
      SIPParser(void) {}
      virtual ~SIPParser(void) {}

      std::shared_ptr<sip0x::SIPMessage> parse(sip0x::Utils::InputTokenStream& iss) {
        FactoryContext ctx;

        ReadResult res = sip0x::Parser::parse(iss, grammar, &ctx);
        if (res.successes) {
          FactoryContextSIPMessage* message = dynamic_cast<FactoryContextSIPMessage*>(ctx._children[0]);
          if (message != nullptr) {
            if (message->is_request()) {
              return std::shared_ptr<sip0x::SIPMessage>(new SIPRequest(message->request()));
            }
            else {
              return std::shared_ptr<sip0x::SIPMessage>(new SIPResponse(message->response()));
            }
          }
        }
        return nullptr;
      }
    };
  }
}

#endif // SIP0X_PARSER_SIPPARSER_HPP__
