#if !defined(SIP0X_PARSER_PARSER_HPP__)
#define SIP0X_PARSER_PARSER_HPP__

#include "utils/InputTokenStream.hpp"
#include "parser/ParserResult.hpp"

#include <mutex>

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
    private:
      static std::recursive_mutex _sigleton_mtx;
      static TokenAbstract* _sip_grammar;

      Parser(void) {}
      virtual ~Parser(void) {}

    public:
      //! Load grammar of SIP parser. This is high recommended because grammar load phase take several seconds.
      static void load_grammar(void);

      //! Parse an input stream using the grammar root and building structure from factory.
      static ParserResult parse(sip0x::utils::InputTokenStream& iss, TokenAbstract const& root, FactoryContext* factory);

      //! Parse an input stream to a SIPMessage.
      //! \return NULL in case of failure.
      static std::shared_ptr<sip0x::protocol::SIPMessage> parse(sip0x::utils::InputTokenStream& iss);
      
    };
  }
}

#endif // SIP0X_PARSER_PARSER_HPP__
