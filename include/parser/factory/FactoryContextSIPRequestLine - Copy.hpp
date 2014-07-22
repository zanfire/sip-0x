#if !defined(SIP0X_PARSER_FACTORYCONTEXTREQUESTLINE_HPP__)
#define SIP0X_PARSER_FACTORYCONTEXTREQUESTLINE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/factory/FactoryContextEx.hpp"

#include "protocol/SIP.hpp"

namespace Sip0x
{
  namespace Parser
  {
    using namespace Sip0x::Protocol;

    class FactoryContextRequestLine : public FactoryContext {
    protected:
    public:
      
      //virtual void handle_create(TokenAbstract const* token, ReadResult const& result) override {
        //_type = new SIPMessage();
      //}

      //virtual void handle_destroy(void) override {
        //delete _type;
      //}
    };
  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXTREQUESTLINE_HPP__
