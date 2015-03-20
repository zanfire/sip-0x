#include "parser/tokens/TokenAbstract.hpp"

#include "parser/factory/FactoryContext.hpp"


#include "utils/LoggerFactory.hpp"

#include "utils/Logger.hpp"

#include "utils/InputTokenStream.hpp"

using namespace sip0x::utils;
using namespace sip0x::parser;

// TODO: root is not a needed argument REMOVE
TokenAbstract::TokenAbstract(std::string name, TokenAbstract* root) : _name(name) {
  std::string logger_category;
  if (name.length() > 0) {
    logger_category = "sip0x.parser.Token." + name;
  }
  else {
    logger_category = "sip0x.parser.Token";
  }
  _logger = LoggerFactory::get_logger(logger_category.c_str());
}

TokenAbstract::~TokenAbstract(void) {

}


ParserResult TokenAbstract::read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const {
  int initial_pos = iss.pos();
  
  LOG_DEBUG(_logger, "Saved position %lld during parsing.", (long long)initial_pos);

  FactoryContext* factory = create_factory();
  ParserResult output = handle_read(iss, factory != nullptr ? factory : ctx);

  if (output.success()) {
    //LOG_DEBUG(_logger, "Consumed chars %d during parsing, parsed %s.", delta, parsed.c_str());
  }
  else {
    iss.seekg(initial_pos);
   LOG_DEBUG(_logger, "Restored position %lld during parsing.", (long long)initial_pos);
    output.push_event(ParserResult::TYPE_NOTICE, initial_pos, "Failed parsing token " + get_name());
  }

  if (output.success()) {
    if (factory != nullptr) {
      factory->create(iss.str(initial_pos, iss.pos() - initial_pos));
      ctx->add_child(factory);
    }
  }
  else {
    if (factory != nullptr) {
      delete factory;
    }
  }
  return output;
}


FactoryContext* TokenAbstract::create_factory(void) const {
  return nullptr;
}
