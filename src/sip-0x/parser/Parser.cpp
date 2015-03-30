#include "parser/Parser.hpp"

#include "parser/tokens/TokenSIPMessage.hpp"
#include "parser/factory/FactoryContext.hpp"
#include "parser/tokens/TokenAbstract.hpp"
#include "utils/InputTokenStream.hpp"
#include "protocol/SIP.hpp"

using namespace sip0x::parser;

// Initialize statically the grammar. 
TokenAbstract* Parser::sip_grammar = new TokenSIPMessage();


ParserResult Parser::parse(sip0x::utils::InputTokenStream& iss, TokenAbstract const& root, FactoryContext* factory) {

#if defined(ENABLE_PARSER_LOGGING)
  std::shared_ptr<Logger> logger = LoggerFactory::get_logger("sip0x.Parser.Parser");
  LOG_DEBUG(logger, "Parsing string \"%s\".", iss.str());
#endif

  ParserResult result = root.read(iss, factory);

  if (!iss.eof()) {
    // No consumed all input.
    int cur_pos = iss.pos();
    result.push_event(ParserResult::TYPE_ERROR, cur_pos, "Left content.");
  }
  return result;
}



std::shared_ptr<sip0x::protocol::SIPMessage> Parser::parse(sip0x::utils::InputTokenStream& iss) {
  
  FactoryContext ctx;

  ParserResult res = parse(iss, *sip_grammar, &ctx);
  if (res.success()) {
    FactoryContextSIPMessage* message = dynamic_cast<FactoryContextSIPMessage*>(ctx._children[0]);
    if (message != nullptr) {
      return message->get_message();
    }
  }

  for (auto ev : res.get_events()) {
    std::cout << "Type " << (int)(ev.type) << ", message: " << ev.message << std::endl;
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