#if !defined(SIP0X_PARSER_TOKENSIPSTATUSLINE_HPP__)
#define SIP0X_PARSER_TOKENSIPSTATUSLINE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"

#include "parser/common/TokenPresets.hpp"

#include "parser/sip/TokenSIPURI.hpp"
#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/TokenSIPVersion.hpp"

namespace Sip0x
{
  namespace Parser
  {
    //
    // Informational  =  "100"  ;  Trying
    // /   "180"  ;  Ringing
    // /   "181"  ;  Call Is Being Forwarded
    // /   "182"  ;  Queued
    // /   "183"  ;  Session Progress
    //
    //
    // Success  =  "200"  ;  OK
    //
    // Redirection  =  "300"  ;  Multiple Choices
    // /   "301"  ;  Moved Permanently
    // /   "302"  ;  Moved Temporarily
    // /   "305"  ;  Use Proxy
    // /   "380"  ;  Alternative Service
    //
    // Client-Error  =  "400"  ;  Bad Request
    // /   "401"  ;  Unauthorized
    // /   "402"  ;  Payment Required
    // /   "403"  ;  Forbidden
    // /   "404"  ;  Not Found
    // /   "405"  ;  Method Not Allowed
    // /   "406"  ;  Not Acceptable
    // /   "407"  ;  Proxy Authentication Required
    // /   "408"  ;  Request Timeout
    // /   "410"  ;  Gone
    // /   "413"  ;  Request Entity Too Large
    // /   "414"  ;  Request-URI Too Large
    // /   "415"  ;  Unsupported Media Type
    // /   "416"  ;  Unsupported URI Scheme
    // /   "420"  ;  Bad Extension
    // /   "421"  ;  Extension Required
    // /   "423"  ;  Interval Too Brief
    // /   "480"  ;  Temporarily not available
    // /   "481"  ;  Call Leg/Transaction Does Not Exist
    // /   "482"  ;  Loop Detected
    // /   "483"  ;  Too Many Hops
    // /   "484"  ;  Address Incomplete
    // /   "485"  ;  Ambiguous
    // /   "486"  ;  Busy Here
    // /   "487"  ;  Request Terminated
    // /   "488"  ;  Not Acceptable Here
    // /   "491"  ;  Request Pending
    // /   "493"  ;  Undecipherable
    //
    // Server-Error  =  "500"  ;  Internal Server Error
    // /   "501"  ;  Not Implemented
    // /   "502"  ;  Bad Gateway
    // /   "503"  ;  Service Unavailable
    // /   "504"  ;  Server Time-out
    // /   "505"  ;  SIP Version not supported
    // /   "513"  ;  Message Too Large
    //
    //
    //
    // Global-Failure  =  "600"  ;  Busy Everywhere
    // /   "603"  ;  Decline
    // /   "604"  ;  Does not exist anywhere
    // /   "606"  ;  Not Acceptable

    // Status-Line     =  SIP-Version SP Status-Code SP Reason-Phrase CRLF
    // Status-Code     =  Informational
    // /   Redirection
    // /   Success
    // /   Client-Error
    // /   Server-Error
    // /   Global-Failure
    // /   extension-code
    // extension-code  =  3DIGIT
    // Reason-Phrase   =  *(reserved / unreserved / escaped
    // / UTF8-NONASCII / UTF8-CONT / SP / HTAB)
    class TokenSIPStatusLine : public TokenAbstract {

    protected:
      Sequence<TokenSIPVersion, TokenSP, TokenRegex , TokenSP, TokenRegex, TokenCRLF> _sequence;
      
    public:
      TokenSIPStatusLine(void) : TokenAbstract("SIPStatusLine"),
        _sequence
        (
          TokenSIPVersion(),
          TokenSP(),
          TokenRegex("[0-9]{3}"),
          TokenSP(),
          TokenRegex("((" + RegexConstStrings::reserved + ")|(" + RegexConstStrings::unreserved + ")|(" + RegexConstStrings::escaped + ")|(" + RegexConstStrings::UTF8_NONASCII + ")|(" + RegexConstStrings::UTF8_CONT + ")|(" + RegexConstStrings::SP + ")|(" + RegexConstStrings::HTAB + "))*"),
          TokenCRLF()
        )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPStatusLine");
      }

      virtual ~TokenSIPStatusLine(void) { }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        return _sequence.read(iss, ctx);
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENSIPSTATUSLINE_HPP__
