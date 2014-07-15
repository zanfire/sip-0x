#if !defined(SIP0X_PARSER_TOKENABSOLUTEURI_HPP__)
#define SIP0X_PARSER_TOKENABSOLUTEURI_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Token.hpp"
#include "parser/base/TokenRegex.hpp"
#include "parser/base/Operators.hpp"

#include "parser/common/RegexConstStrings.hpp"
#include "parser/common/TokenPresets.hpp"
#include "parser/common/TokenQuotedString.hpp"

namespace Sip0x
{
  namespace Parser
  {
    // TODO: Need to be implemented !!!

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
    class TokenAbsoluteURI : public TokenAbstract {

    protected:
      Sequence<TokenRegex, Token, TokenRegex> _sequence;

    public:
      TokenAbsoluteURI(void) : TokenAbstract("TokenAbsoluteURI"),
        _sequence(
          TokenRegex("scheme", RegexConstStrings::token),
          Token(":"),
          TokenRegex("((" + RegexConstStrings::qdtext + ")|(" + RegexConstStrings::quoted_pair + "))*")
         )
       {
      }


    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult result = _sequence.read(iss, ctx);
        return result;
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENABSOLUTEURI_HPP__
