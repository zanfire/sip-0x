#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"

#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"
#include "parser/sip/TokenSIPMessageHeader_CSeq.hpp"

namespace Sip0x
{
  namespace Parser
  {

    // message - header = (Accept
    //   / Accept - Encoding
    //   / Accept - Language
    //   / Alert - Info
    //   / Allow
    //   / Authentication - Info
    //   / Authorization
    //   / Call - ID
    //   / Call - Info
    //   / Contact
    //   / Content - Disposition
    //   / Content - Encoding
    //   / Content - Language
    //   / Content - Length
    //   / Content - Type
    //   / CSeq
    //   / Date
    //   / Error - Info
    //   / Expires
    //   / From
    //   / In - Reply - To
    //   / Max - Forwards
    //   / MIME - Version
    //   / Min - Expires
    //   / Organization
    //   / Priority
    //   / Proxy - Authenticate
    //   / Proxy - Authorization
    //   / Proxy - Require
    //   / Record - Route
    //   / Reply - To
    //   / Require
    //   / Retry - After
    //   / Route
    //   / Server
    //   / Subject
    //   / Supported
    //   / Timestamp
    //   / To
    //   / Unsupported
    //   / User - Agent
    //   / Via
    //   / Warning
    //   / WWW - Authenticate
    //   / extension - header) CRLF
    

    class TokenSIPMessageHeader : public TokenAbstract {

    protected:
      Sequence<Alternative<TokenSIPMessageHeader_CSeq, Token>, Token> _sequence;

    public:
      TokenSIPMessageHeader(void) : TokenAbstract("SIPMessageHeader"),
        _sequence
        (
        Alternative<TokenSIPMessageHeader_CSeq, Token>
        (
          TokenSIPMessageHeader_CSeq(),
          Token("xxxx")
        ),
        Token("\r\n")
        )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMessageHeader");
      }

      virtual ~TokenSIPMessageHeader(void) { }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _sequence.read(iss);
        return r;
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_HPP__
