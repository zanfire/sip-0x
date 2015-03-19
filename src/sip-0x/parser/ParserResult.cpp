#include "parser/ParserResult.hpp"

using namespace sip0x::parser;


ParserResult::ParserResult(void) {
  _success = false;
  _pos = 0;
  _len = 0;
}


ParserResult::ParserResult(bool success, uint32_t pos, uint32_t len) {
  _success = success;
  _pos = pos;
  _len = len;
}


ParserResult::~ParserResult(void) {

}


bool ParserResult::success(void) {
  return (_pos == _len) && !contains_events(TYPE_ERROR);
}


void ParserResult::set_position(int pos) {
  _pos = pos;
}


void ParserResult::push_event(ParserEventType type, int pos, std::string message) {
  ParserEvent ev = { type, pos, message };
  _events.push_back(ev);
  if (type == TYPE_ERROR) {
    _success = false;
  }
}


ParserResult::ParserEvent ParserResult::get_error(int start_index) {
  for (std::size_t i = start_index; i < _events.size(); i++) {
    ParserEvent ev = _events.at(i);
    if (ev.type == TYPE_ERROR) {
      return ev;
    }
  }
  return { TYPE_NOTICE, 0, 0 };
}


bool ParserResult::contains_events(ParserEventType type) {
  for (auto ev : _events) {
    if (ev.type == type) return true;
  }
  return false;
}
