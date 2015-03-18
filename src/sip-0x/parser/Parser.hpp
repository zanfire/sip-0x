#if !defined(SIP0X_PARSER_PARSER_HPP__)
#define SIP0X_PARSER_PARSER_HPP__

//#include "parser/factory/FactoryContext.hpp"
//#include "parser/tokens/TokenAbstract.hpp"

#include "utils/InputTokenStream.hpp"
#include "parser/ParserResult.hpp"


namespace sip0x
{
  class SIPMessage;

  namespace {
    class InputTokenStream;
  }

  namespace parser
  {
    class TokenAbstract;
    class FactoryContext;

    //static ParserResult parse(sip0x::utils::InputTokenStream& iss, sip0x::parser::TokenAbstract const& root, sip0x::parser::FactoryContext* factory);
    static ParserResult parse(sip0x::utils::InputTokenStream& iss, TokenAbstract& root, FactoryContext* factory);
    

    static std::shared_ptr<sip0x::SIPMessage> parse(sip0x::utils::InputTokenStream& iss);
    // Deprecated stuff
    
    //static ParserResult parse(std::string text, TokenAbstract& root, FactoryContext* factory);
    //static sip0x::SIPMessage* parse_sip_message(sip0x::utils::InputTokenStream&  iss);
    //static sip0x::SIPMessage* parse_sip_message(std::string text);
  }
}

#endif // SIP0X_PARSER_PARSER_HPP__
