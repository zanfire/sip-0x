#if !defined(SIP0X_PARSER_PARSER_HPP__)
#define SIP0X_PARSER_PARSER_HPP__

#include <vector>
#include <sstream>
#include <iostream>
#include <memory>

#include "parser/base/TokenAbstract.hpp"
#include "parser/sip/TokenSIPMessage.hpp"
#include "parser/factory/FactoryContext.hpp"

#include "utils/log/Logger.hpp"
#include "utils/log/LoggerManager.hpp"

#include "protocol/SIP.hpp"


namespace sip0x
{
  namespace Parser
  {
    using namespace sip0x::Utils::Log;

    static ReadResult parse(sip0x::Utils::InputTokenStream& iss, TokenAbstract& root, FactoryContext* factory) {
#if defined(ENABLE_PARSER_LOGGING)
      std::shared_ptr<Logger> logger = LoggerManager::get_logger("sip0x.Parser.Parser");
      LOG_DEBUG(logger, "Parsing string \"%s\".", iss.str());
#endif

      ReadResult result = root.read(iss, factory);

      if (result.successes && iss.eof()) {
#if defined(ENABLE_PARSER_LOGGING)
        LOG_DEBUG(logger, "Parsing successes, remains: %d, pos %d.", iss.remains(), iss.pos());
#endif
      }
      else {
        // No consumed all input.
        result.successes = false;

        int cur_pos = iss.pos();
        std::string r = iss.get();
        
        if (result.errorpos == -2) {
          result.set_error(cur_pos, "Remaining string: " + r);
        }
#if defined(ENABLE_PARSER_LOGGING)
        LOG_DEBUG(logger, "Parsing terminated without successes, remaining string: \"%s\".", r.c_str());
#endif
      }
      return result;
    }

    static ReadResult parse(std::string text, TokenAbstract& root, FactoryContext* factory) {
      sip0x::Utils::InputTokenStream iss(text);
      return parse(iss, root, factory);
    }

    static sip0x::SIPMessage* parse_sip_message(sip0x::Utils::InputTokenStream&  iss) {
      static TokenSIPMessage sip; // Expensive to build
      FactoryContext ctx;

      ReadResult res = parse(iss, sip, &ctx);
      if (res.successes) {
        FactoryContextSIPMessage* message = dynamic_cast<FactoryContextSIPMessage*>(ctx._children[0]);
        if (message != nullptr) {
          if (message->is_request()) {
            return new SIPRequest(message->request());
          }
          else {
            return new SIPResponse(message->response());
          }
        }
      }

      return nullptr;
    }

    static sip0x::SIPMessage* parse_sip_message(std::string text) {
      sip0x::Utils::InputTokenStream iss(text);
      return parse_sip_message(iss);
    }
  }
}

#endif // SIP0X_PARSER_PARSER_HPP__
