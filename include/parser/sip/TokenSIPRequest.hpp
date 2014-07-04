#if !defined(SIP0X_PARSER_TOKENSIPREQUEST_HPP__)
#define SIP0X_PARSER_TOKENSIPREQUEST_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"

#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"

#include "parser/sip/TokenSIPRequestLine.hpp"
#include "parser/sip/TokenSIPMessageHeader.hpp"

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



namespace Sip0x
{
  namespace Parser
  {

    // Request        =  Request-Line
    //                   *( message-header )
    //                   CRLF
    //                   [ message-body ]
    class TokenSIPRequest : public TokenAbstract {

    protected:
      Sequence<TokenSIPRequestLine, Occurrence<TokenSIPMessageHeader>, Token, TokenRegex> _sequence;
      
    public:
      TokenSIPRequest(void) : TokenAbstract("SIPRequest"),
        _sequence(
          TokenSIPRequestLine(), 
          Occurrence<TokenSIPMessageHeader>(TokenSIPMessageHeader(), 0, -1), 
          Token("\r\n"), 
          TokenRegex(".*")
         )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPRequest");
      }

      virtual ~TokenSIPRequest(void) { }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r; // = _sequence.read(iss, ui);
        return r;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPREQUEST_HPP__
