#include "parser/Parser.hpp"

#include "parser/tokens/TokenSIPMessage.hpp"
#include "parser/factory/FactoryContext.hpp"
#include "parser/tokens/TokenAbstract.hpp"
#include "utils/InputTokenStream.hpp"
#include "protocol/SIP.hpp"

using namespace sip0x::parser;

std::recursive_mutex Parser::_sigleton_mtx;
// Don't initialize statically sip grammar because it's depends on other 
// statics (regex expressions). So, this lead to an incomplete initialization.
TokenAbstract* Parser::_sip_grammar = nullptr; 

void Parser::load_grammar(void) {
  if (_sip_grammar != nullptr) return; // Loaded 
  _sigleton_mtx.lock();
  if (_sip_grammar == nullptr) {
    _sip_grammar = new TokenSIPMessage();
  }
  _sigleton_mtx.unlock();
}


ParserResult Parser::parse(sip0x::utils::InputTokenStream& iss, TokenAbstract const& root, FactoryContext* factory) {
  ParserResult result = root.read(iss, factory);
  if (!iss.eof()) {
    // No consumed all input.
    result.push_event(ParserResult::TYPE_ERROR, iss.pos(), "Left content.");
  }
  return result;
}


std::shared_ptr<sip0x::protocol::SIPMessage> Parser::parse(sip0x::utils::InputTokenStream& iss) {
  FactoryContext ctx;
  load_grammar();
  ParserResult res = parse(iss, *_sip_grammar, &ctx);
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
