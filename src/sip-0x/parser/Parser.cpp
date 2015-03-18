#include "parser/Parser.hpp"

//#include <vector>
//#include <sstream>
//#include <iostream>
//#include <memory>

#include "parser/tokens/TokenSIPMessage.hpp"
#include "parser/factory/FactoryContext.hpp"
#include "parser/tokens/TokenAbstract.hpp"

#include "utils/InputTokenStream.hpp"

//
//#include "utils/Logger.hpp"
//#include "utils/LoggerFactory.hpp"
//
#include "protocol/SIP.hpp"

using namespace sip0x::utils;
using namespace sip0x::parser;

ParserResult sip0x::parser::parse(sip0x::utils::InputTokenStream& iss, TokenAbstract& root, FactoryContext* factory) {

#if defined(ENABLE_PARSER_LOGGING)
  std::shared_ptr<Logger> logger = LoggerFactory::get_logger("sip0x.Parser.Parser");
  LOG_DEBUG(logger, "Parsing string \"%s\".", iss.str());
#endif

  ParserResult result = root.read(iss, factory);

  if (!result.success() /*&& !iss.eof()*/) {
    // No consumed all input.
    //result.successes = false;
    int cur_pos = iss.pos();
    result.push_event(ParserResult::TYPE_ERROR, cur_pos, "Left content.");
  }
  return result;
}



static std::shared_ptr<sip0x::SIPMessage> sip0x::parser::parse(sip0x::utils::InputTokenStream& iss) {
  static TokenSIPMessage grammar;

  FactoryContext ctx;

  ParserResult res = parse(iss, grammar, &ctx);
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

/*
ParserResult parse(std::string text, TokenAbstract& root, FactoryContext* factory) {
  sip0x::utils::InputTokenStream iss(text);
  return parse(iss, root, factory);
}

sip0x::SIPMessage* parse_sip_message(sip0x::utils::InputTokenStream&  iss) {
  static TokenSIPMessage sip; // Expensive to build
  FactoryContext ctx;

  ParserResult res = parse(iss, sip, &ctx);
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


sip0x::SIPMessage* parse_sip_message(std::string text) {
  sip0x::utils::InputTokenStream iss(text);
  return parse_sip_message(iss);
}
*/