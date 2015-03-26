#if !defined(SIP0X_PARSER_PARSER_HPP__)
#define SIP0X_PARSER_PARSER_HPP__

//#include "parser/factory/FactoryContext.hpp"
//#include "parser/tokens/TokenAbstract.hpp"

#include "utils/InputTokenStream.hpp"
#include "parser/ParserResult.hpp"


namespace sip0x
{
  namespace protocol {
    class SIPMessage;
  }

  namespace utils {
    class InputTokenStream;
  }

  namespace parser
  {
    class TokenAbstract;
    class FactoryContext;

    class Parser {
    public:
      static TokenAbstract* sip_grammar;

      //! Parse an input stream using the grammar root and building structure from factory.
      static ParserResult parse(sip0x::utils::InputTokenStream& iss, TokenAbstract const& root, FactoryContext* factory);

      //! Parse an input stream to a SIPMessage.
      //! \return NULL in case of failure.
      static std::shared_ptr<sip0x::protocol::SIPMessage> parse(sip0x::utils::InputTokenStream& iss);
      
    };
  }
}

#endif // SIP0X_PARSER_PARSER_HPP__
