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
  unsigned long initial_pos = iss.pos();
  
  LOG_DEBUG(_logger, "PUSH %5lu, type: %s.", initial_pos, get_name().c_str());

  FactoryContext* factory = create_factory();
  ParserResult output = handle_read(iss, factory != nullptr ? factory : ctx);

  if (output.success()) {
    LOG_DEBUG(_logger, "GOT  %5lu, type: %s.", initial_pos, get_name().c_str());
  }
  else {
    iss.seekg(initial_pos);
    LOG_DEBUG(_logger, "POP  %5lu, type: %s.", initial_pos, get_name().c_str());
    output.push_event(ParserResult::TYPE_NOTICE, initial_pos, "Failed parsing token " + get_name());
  }

  if (factory != nullptr) {
    if (output.success()) {
      factory->create(iss.str(initial_pos, iss.pos() - initial_pos));
      ctx->add_child(factory);
    }
    else {
      delete factory;
    }
  }
  return output;
}


FactoryContext* TokenAbstract::create_factory(void) const {
  return nullptr;
}
