#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"

// SIP-message    =  Request / Response
// Request        =  Request-Line
//                   *( message-header )
//                   CRLF
//                   [ message-body ]
// Request-Line   =  Method SP Request-URI SP SIP-Version CRLF
// Request-URI    =  SIP-URI / SIPS-URI / absoluteURI
// absoluteURI    =  scheme ":" ( hier-part / opaque-part )
// hier-part      =  ( net-path / abs-path ) [ "?" query ]
// net-path       =  "//" authority [ abs-path ]
// abs-path       =  "/" path-segments
// 
// opaque-part    =  uric-no-slash *uric
// uric           =  reserved / unreserved / escaped
// uric-no-slash  =  unreserved / escaped / ";" / "?" / ":" / "@"
//                   / "&" / "=" / "+" / "$" / ","
// path-segments  =  segment *( "/" segment )
// segment        =  *pchar *( ";" param )
// param          =  *pchar
// pchar          =  unreserved / escaped /
//                   ":" / "@" / "&" / "=" / "+" / "$" / ","
// scheme         =  ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
// authority      =  srvr / reg-name
// srvr           =  [ [ userinfo "@" ] hostport ]
// reg-name       =  1*( unreserved / escaped / "$" / ","
//                   / ";" / ":" / "@" / "&" / "=" / "+" )
// query          =  *uric
// SIP-Version    =  "SIP" "/" 1*DIGIT "." 1*DIGIT



namespace Sip0x
{
  namespace Parser
  {

    // Request        =  Request-Line
    //                   *( message-header )
    //                   CRLF
    //                   [ message-body ]
    class TokenSIPMessageHeader : public TokenAbstract {

    protected:
      // it is magic ... no is nested template.
      //Sequence<TokenSIPRequestLine, Occurrence<TokenSIPMessageHeader>, Token, TokenRegex> _sequence;
      
    public:
      TokenSIPMessageHeader(void) : TokenAbstract("SIPMessageHeader")
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMessageHeader");
      }

      virtual ~TokenSIPMessageHeader(void) { }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r; // = _sequence.read(iss, ui);
        return r;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_HPP__
