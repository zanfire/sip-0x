#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"

#include "parser/sip/messageheaders/TokenSIPMessageHeader_Accept.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Accept_Encoding.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Accept_Language.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Alert_Info.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Allow.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Authentication_Info.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Authorization.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Call_ID.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Call_Info.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Contact.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Content_Disposition.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Content_Encoding.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Content_Language.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Content_Length.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Content_Type.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_CSeq.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Date.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Error_Info.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Expires.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_extension_header.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_From.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_In_Reply_To.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Max_Forwards.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_MIME_Version.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Min_Expires.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Organization.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Priority.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Proxy_Authenticate.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Proxy_Authorization.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Proxy_Require.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Record_Route.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Reply_To.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Require.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Retry_After.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Route.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Server.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Subject.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Supported.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Timestamp.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_To.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Unsupported.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_User_Agent.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Via.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_Warning.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_WWW_Authenticate.hpp"


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
      Sequence<Alternative<
      TokenSIPMessageHeader_Accept,
      TokenSIPMessageHeader_Accept_Encoding,
      TokenSIPMessageHeader_Accept_Language,
      TokenSIPMessageHeader_Alert_Info,
      TokenSIPMessageHeader_Allow,
      TokenSIPMessageHeader_Authentication_Info,
      TokenSIPMessageHeader_Authorization,
      TokenSIPMessageHeader_Call_ID,
      TokenSIPMessageHeader_Call_Info,
      TokenSIPMessageHeader_Contact,
      TokenSIPMessageHeader_Content_Disposition,
      TokenSIPMessageHeader_Content_Encoding,
      TokenSIPMessageHeader_Content_Language,
      TokenSIPMessageHeader_Content_Length,
      TokenSIPMessageHeader_Content_Type,
      TokenSIPMessageHeader_CSeq,
      TokenSIPMessageHeader_Date,
      //TokenSIPMessageHeader_Error_Info,
      //TokenSIPMessageHeader_Expires,
      //TokenSIPMessageHeader_extension_header,
      TokenSIPMessageHeader_From,
      //TokenSIPMessageHeader_In_Reply_To,
      TokenSIPMessageHeader_Max_Forwards,
      //TokenSIPMessageHeader_MIME_Version,
      //TokenSIPMessageHeader_Min_Expires,
      //TokenSIPMessageHeader_Organization,
      //TokenSIPMessageHeader_Priority,
      //TokenSIPMessageHeader_Proxy_Authenticate,
      //TokenSIPMessageHeader_Proxy_Authorization,
      //TokenSIPMessageHeader_Proxy_Require,
      //TokenSIPMessageHeader_Record_Route,
      //TokenSIPMessageHeader_Reply_To,
      //TokenSIPMessageHeader_Require,
      //TokenSIPMessageHeader_Retry_After,
      //TokenSIPMessageHeader_Route,
      //TokenSIPMessageHeader_Server,
      //TokenSIPMessageHeader_Subject,
      //TokenSIPMessageHeader_Supported,
      //TokenSIPMessageHeader_Timestamp,
      TokenSIPMessageHeader_To,
      //TokenSIPMessageHeader_Unsupported,
      //TokenSIPMessageHeader_User_Agent,
      TokenSIPMessageHeader_Via
      //TokenSIPMessageHeader_Warning,
      //TokenSIPMessageHeader_WWW_Authenticate
      >, TokenCRLF> _sequence;

    public:
      TokenSIPMessageHeader(void) : TokenAbstract("SIPMessageHeader"),
        _sequence
        (
        Alternative
        <
        TokenSIPMessageHeader_Accept,
        TokenSIPMessageHeader_Accept_Encoding,
        TokenSIPMessageHeader_Accept_Language,
        TokenSIPMessageHeader_Alert_Info,
        TokenSIPMessageHeader_Allow,
        TokenSIPMessageHeader_Authentication_Info,
        TokenSIPMessageHeader_Authorization,
        TokenSIPMessageHeader_Call_ID,
        TokenSIPMessageHeader_Call_Info,
        TokenSIPMessageHeader_Contact,
        TokenSIPMessageHeader_Content_Disposition,
        TokenSIPMessageHeader_Content_Encoding,
        TokenSIPMessageHeader_Content_Language,
        TokenSIPMessageHeader_Content_Length,
        TokenSIPMessageHeader_Content_Type,
        TokenSIPMessageHeader_CSeq,
        TokenSIPMessageHeader_Date,
        //TokenSIPMessageHeader_Error_Info,
        //TokenSIPMessageHeader_Expires,
        //TokenSIPMessageHeader_extension_header,
        TokenSIPMessageHeader_From,
        //TokenSIPMessageHeader_In_Reply_To,
        TokenSIPMessageHeader_Max_Forwards,
        //TokenSIPMessageHeader_MIME_Version,
        //TokenSIPMessageHeader_Min_Expires,
        //TokenSIPMessageHeader_Organization,
        //TokenSIPMessageHeader_Priority,
        //TokenSIPMessageHeader_Proxy_Authenticate,
        //TokenSIPMessageHeader_Proxy_Authorization,
        //TokenSIPMessageHeader_Proxy_Require,
        //TokenSIPMessageHeader_Record_Route,
        //TokenSIPMessageHeader_Reply_To,
        //TokenSIPMessageHeader_Require,
        //TokenSIPMessageHeader_Retry_After,
        //TokenSIPMessageHeader_Route,
        //TokenSIPMessageHeader_Server,
        //TokenSIPMessageHeader_Subject,
        //TokenSIPMessageHeader_Supported,
        //TokenSIPMessageHeader_Timestamp,
        TokenSIPMessageHeader_To,
        //TokenSIPMessageHeader_Unsupported,
        //TokenSIPMessageHeader_User_Agent,
        TokenSIPMessageHeader_Via
        //TokenSIPMessageHeader_Warning,
        //TokenSIPMessageHeader_WWW_Authenticate
        >
        (
      TokenSIPMessageHeader_Accept(),
      TokenSIPMessageHeader_Accept_Encoding(),
      TokenSIPMessageHeader_Accept_Language(),
      TokenSIPMessageHeader_Alert_Info(),
      TokenSIPMessageHeader_Allow(),
      TokenSIPMessageHeader_Authentication_Info(),
      TokenSIPMessageHeader_Authorization(),
      TokenSIPMessageHeader_Call_ID(),
      TokenSIPMessageHeader_Call_Info(),
      TokenSIPMessageHeader_Contact(),
      TokenSIPMessageHeader_Content_Disposition(),
      TokenSIPMessageHeader_Content_Encoding(),
      TokenSIPMessageHeader_Content_Language(),
      TokenSIPMessageHeader_Content_Length(),
      TokenSIPMessageHeader_Content_Type(),
      TokenSIPMessageHeader_CSeq(),
      TokenSIPMessageHeader_Date(),
      //TokenSIPMessageHeader_Error_Info(),
      //TokenSIPMessageHeader_Expires(),
      //TokenSIPMessageHeader_extension_header(),
      TokenSIPMessageHeader_From(),
      //TokenSIPMessageHeader_In_Reply_To(),
      TokenSIPMessageHeader_Max_Forwards(),
      //TokenSIPMessageHeader_MIME_Version(),
      //TokenSIPMessageHeader_Min_Expires(),
      //TokenSIPMessageHeader_Organization(),
      //TokenSIPMessageHeader_Priority(),
      //TokenSIPMessageHeader_Proxy_Authenticate(),
      //TokenSIPMessageHeader_Proxy_Authorization(),
      //TokenSIPMessageHeader_Proxy_Require(),
      //TokenSIPMessageHeader_Record_Route(),
      //TokenSIPMessageHeader_Reply_To(),
      //TokenSIPMessageHeader_Require(),
      //TokenSIPMessageHeader_Retry_After(),
      //TokenSIPMessageHeader_Route(),
      //TokenSIPMessageHeader_Server(),
      //TokenSIPMessageHeader_Subject(),
      //TokenSIPMessageHeader_Supported(),
      //TokenSIPMessageHeader_Timestamp(),
      TokenSIPMessageHeader_To(),
      //TokenSIPMessageHeader_Unsupported(),
      //TokenSIPMessageHeader_User_Agent(),
      TokenSIPMessageHeader_Via()
      //TokenSIPMessageHeader_Warning(),
      //TokenSIPMessageHeader_WWW_Authenticate()
        ),
        TokenCRLF()
        )
      {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenSIPMessageHeader");
      }

    protected:
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, void* ctx) const override {
        ReadResult r = _sequence.read(iss);
        return r;
      }
    };

  }
}

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_HPP__
