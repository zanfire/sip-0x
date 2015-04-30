#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_AUTHORIZATION_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_AUTHORIZATION_HPP__

#include "parser/tokens/TokenAbstract.hpp"
#include "parser/tokens/Operators.hpp"
#include "parser/tokens/TokenRegex.hpp"



#include "parser/tokens/TokenSIPMethod.hpp"
#include "parser/tokens/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace parser
  {
    // Authorization     =  "Authorization" HCOLON credentials
    // credentials       =  ("Digest" LWS digest-response)
    //                      / other-response
    // digest-response   =  dig-resp *(COMMA dig-resp)
    // dig-resp          =  username / realm / nonce / digest-uri
    //                       / dresponse / algorithm / cnonce
    //                       / opaque / message-qop
    //                       / nonce-count / auth-param
    // username          =  "username" EQUAL username-value
    // username-value    =  quoted-string
    // digest-uri        =  "uri" EQUAL LDQUOT digest-uri-value RDQUOT
    // digest-uri-value  =  rquest-uri ; Equal to request-uri as specified
    //                      by HTTP/1.1
    // message-qop       =  "qop" EQUAL qop-value
    // 
    // cnonce            =  "cnonce" EQUAL cnonce-value
    // cnonce-value      =  nonce-value
    // nonce-count       =  "nc" EQUAL nc-value
    // nc-value          =  8LHEX
    // dresponse         =  "response" EQUAL request-digest
    // request-digest    =  LDQUOT 32LHEX RDQUOT
    // auth-param        =  auth-param-name EQUAL
    //                      ( token / quoted-string )
    // auth-param-name   =  token
    // other-response    =  auth-scheme LWS auth-param
    //                      *(COMMA auth-param)
    // auth-scheme       =  token
    class TokenSIPMessageHeader_Authorization : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Authorization() : TokenSIPMessageHeader_base("Authorization", "Authorization",
        Sequence<TokenRegex, TokenLWS, TokenSIPMethod>
        (
          TokenDigits(),
          TokenLWS(),
          TokenSIPMethod()
        )
      )
      {
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_AUTHORIZATION_HPP__
