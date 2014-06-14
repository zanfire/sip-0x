#if 0

#if !defined(SIP0X_PARSER_SIPGRAMMAR_HPP__)
#define SIP0X_PARSER_SIPGRAMMAR_HPP__

#define BOOST_SPIRIT_DEBUG_PRINT_SOME 1

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <string>
#include <vector>

#define Iterator std::string::const_iterator

namespace Sip0x
{
  namespace Parser
  {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace fusion = boost::fusion;
    namespace phoenix = boost::phoenix;

    using qi::int_;
    using qi::lit;
    using qi::double_;
    using qi::repeat;
    using ascii::char_;
    using qi::on_error;
    using qi::fail;
    using ascii::char_;
    using namespace qi::labels;

    using phoenix::construct;
    using phoenix::val;
 
    struct SIPGrammar : qi::grammar<Iterator, std::string()>
    {

      qi::rule<Iterator, std::string()> root;
      // Core rules (from RFC 4234)
      qi::rule<Iterator, std::string()> CRLF;
      qi::rule<Iterator, std::string()> ALPHA;
      qi::rule<Iterator, std::string()> DIGIT;
      qi::rule<Iterator, std::string()> HEXDIG;
      qi::rule<Iterator, std::string()> LWSP;
      qi::rule<Iterator, std::string()> OCTET;
      qi::rule<Iterator, std::string()> SP;
      qi::rule<Iterator, std::string()> VCHAR;
      qi::rule<Iterator, std::string()> WSP;

      qi::rule<Iterator, std::string()> HTAB;
      qi::rule<Iterator, std::string()> DQUOTE;

      qi::rule<Iterator, std::string()> alphanum;

      qi::rule<Iterator, std::string()> reserved;
      qi::rule<Iterator, std::string()> unreserved;
      qi::rule<Iterator, std::string()> mark;
      qi::rule<Iterator, std::string()> escaped;

      qi::rule<Iterator, std::string()> LWS;
      qi::rule<Iterator, std::string()> SWS;

      qi::rule<Iterator, std::string()> STAR;  
      qi::rule<Iterator, std::string()> SLASH; 
      qi::rule<Iterator, std::string()> EQUAL; 
      qi::rule<Iterator, std::string()> LPAREN;
      qi::rule<Iterator, std::string()> RPAREN;
      qi::rule<Iterator, std::string()> RAQUOT;
      qi::rule<Iterator, std::string()> LAQUOT;
      qi::rule<Iterator, std::string()> COMMA; 
      qi::rule<Iterator, std::string()> SEMI;  
      qi::rule<Iterator, std::string()> COLON; 
      qi::rule<Iterator, std::string()> LDQUOT;
      qi::rule<Iterator, std::string()> RDQUOT;

      qi::rule<Iterator, std::string()> HCOLON;

      qi::rule<Iterator, std::string()> TEXT_UTF8_TRIM;
      qi::rule<Iterator, std::string()> TEXT_UTF8char; 
      qi::rule<Iterator, std::string()> UTF8_NONASCII; 
      qi::rule<Iterator, std::string()> UTF8_CONT;     

      qi::rule<Iterator, std::string()> LHEX; //= DIGIT / %x61 - 66; lowercase a - f

      qi::rule<Iterator, std::string()> token;              // = 1 * (alphanum / "-" / "." / "!" / "%" / "*" / "_" / "+" / "`" / "'" / "~")
      qi::rule<Iterator, std::string()> separators;         // = "(" / ")" / "<" / ">" / "@" / "," / ";" / ":" / "\" / DQUOTE / "/" / "[" / "]" / "?" / "=" / "{" / "}" / SP / HTAB
      qi::rule<Iterator, std::string()> word;               // = 1 * (alphanum / "-" / "." / "!" / "%" / "*" / "_" / "+" / "`" / "'" / "~" / "(" / ")" / "<" / ">" / ":" / "\" / DQUOTE / "/" / "[" / "]" / "?" / "{" / "}")

      qi::rule<Iterator, std::string()> comment;            //= LPAREN *(ctext / quoted - pair / comment) RPAREN
      qi::rule<Iterator, std::string()> ctext;              //= %x21 - 27 / %x2A - 5B / %x5D - 7E / UTF8 - NONASCII / LWS

      qi::rule<Iterator, std::string()> quoted_string;      // = SWS DQUOTE *(qdtext / quoted - pair) DQUOTE
      qi::rule<Iterator, std::string()> qdtext;             // = LWS / %x21 / %x23 - 5B / %x5D - 7E / UTF8 - NONASCII

      // Basic rules (from RFC 3261)
      qi::rule<Iterator, std::string()> quoted_pair;        // = "\" (%x00-09 / %x0B-0C / %x0E - 7F)

      qi::rule<Iterator, std::string()> SIP_URI;            // = "sip:"[userinfo] hostport uri_parameters[headers]
      qi::rule<Iterator, std::string()> SIPS_URI;           // = "sips:"[userinfo] hostport uri_parameters[headers]
      qi::rule<Iterator, std::string()> userinfo;           // = (user / telephone - subscriber)[":" password] "@"
      qi::rule<Iterator, std::string()> user;               // = 1 * (unreserved / escaped / user - unreserved)
      qi::rule<Iterator, std::string()> user_unreserved;    // = "&" / "=" / "+" / "$" / "," / ";" / "?" / "/"
      qi::rule<Iterator, std::string()> password;           // = *(unreserved / escaped / "&" / "=" / "+" / "$" / ",")
      qi::rule<Iterator, std::string()> hostport;           // = host[":" port]
      qi::rule<Iterator, std::string()> host;               // = hostname / IPv4address / IPv6reference
      qi::rule<Iterator, std::string()> hostname;           // = *(domainlabel ".") toplabel["."]
      qi::rule<Iterator, std::string()> domainlabel;        // = alphanum / alphanum *(alphanum / "-") alphanum
      qi::rule<Iterator, std::string()> toplabel;           // = ALPHA / ALPHA *(alphanum / "-") alphanum
      qi::rule<Iterator, std::string()> IPv4address;        // = 1 * 3DIGIT "." 1 * 3DIGIT "." 1 * 3DIGIT "." 1 * 3DIGIT
      qi::rule<Iterator, std::string()> IPv6reference;      // = "[" IPv6address "]"
      qi::rule<Iterator, std::string()> IPv6address;        // = hexpart[":" IPv4address]
      qi::rule<Iterator, std::string()> hexpart;            // = hexseq / hexseq "::"[hexseq] / "::"[hexseq]
      qi::rule<Iterator, std::string()> hexseq;             // = hex4 *(":" hex4)
      qi::rule<Iterator, std::string()> hex4;               // = 1 * 4HEXDIG
      qi::rule<Iterator, std::string()> port;               // = 1 * DIGIT

      qi::rule<Iterator, std::string()> uri_parameters;     // = *(";" uri - parameter)
      qi::rule<Iterator, std::string()> uri_parameter;      // = transport - param / user - param / method - param / ttl - param / maddr - param / lr - param / other - param
      qi::rule<Iterator, std::string()> transport_param;    // = "transport="  ("udp" / "tcp" / "sctp" / "tls" / other - transport)
      qi::rule<Iterator, std::string()> other_transport;    // = token
      qi::rule<Iterator, std::string()> user_param;        //= "user=" ("phone" / "ip" / other - user)
      qi::rule<Iterator, std::string()> other_user;        // = token
      qi::rule<Iterator, std::string()> method_param;      // = "method=" Method
      qi::rule<Iterator, std::string()> ttl_param;         // = "ttl=" ttl
      qi::rule<Iterator, std::string()> maddr_param;       // = "maddr=" host
      qi::rule<Iterator, std::string()> lr_param;          // = "lr"
      qi::rule<Iterator, std::string()> other_param;       // = pname["=" pvalue]
      qi::rule<Iterator, std::string()> pname;             // = 1 * paramchar
      qi::rule<Iterator, std::string()> pvalue;            // = 1 * paramchar
      qi::rule<Iterator, std::string()> paramchar;         // = param - unreserved / unreserved / escaped
      qi::rule<Iterator, std::string()> param_unreserved;  // = "[" / "]" / "/" / ":" / "&" / "+" / "$"

      qi::rule<Iterator, std::string()> headers;           // = "?" header *("&" header)
      qi::rule<Iterator, std::string()> header;            // = hname "=" hvalue
      qi::rule<Iterator, std::string()> hname;             // = 1 * (hnv - unreserved / unreserved / escaped)
      qi::rule<Iterator, std::string()> hvalue;            // = *(hnv - unreserved / unreserved / escaped)
      qi::rule<Iterator, std::string()> hnv_unreserved;    // = "[" / "]" / "/" / "?" / ":" / "+" / "$"

      qi::rule<Iterator, std::string()> SIP_message;        // = Request | Response
      qi::rule<Iterator, std::string()> Request;            // = Request_Line *(message_header) CRLF[message_body]
      qi::rule<Iterator, std::string()> Request_Line;       // = Method SP Request_URI SP SIP_Version CRLF
      qi::rule<Iterator, std::string()> RequestURI;         // = SIP_URI | SIPS_URI | absoluteURI
      qi::rule<Iterator, std::string()> absoluteURI;        // = scheme ':' (hier_part | opaque_part)
      qi::rule<Iterator, std::string()> hier_part;          // = (net_path | abs_path)['?' query]
      qi::rule<Iterator, std::string()> net_path;           // = '||' authority[abs_path]
      qi::rule<Iterator, std::string()> abs_path;           // = '|' path_segments

      qi::rule<Iterator, std::string()> opaque_part;        // = uric_no_slash *uric
      qi::rule<Iterator, std::string()> uric;               // = reserved | unreserved | escaped
      qi::rule<Iterator, std::string()> uric_no_slash;      // = unreserved | escaped | ';' | '?' | ':' | '@' | '&' | '=' | '+' | '$' | ','
      qi::rule<Iterator, std::string()> path_segments;      // = segment *('|' segment)
      qi::rule<Iterator, std::string()> segment;            // = *pchar *(';' param)
      qi::rule<Iterator, std::string()> param;              // = *pchar
      qi::rule<Iterator, std::string()> pchar;              // = unreserved | escaped | ':' | '@' | '&' | '=' | '+' | '$' | ','
      qi::rule<Iterator, std::string()> scheme;             // = ALPHA *(ALPHA | DIGIT | '+' | '-' | '.')
      qi::rule<Iterator, std::string()> authority;          // = srvr | reg_name
      qi::rule<Iterator, std::string()> srvr;               // = [[userinfo '@'] hostport]
      qi::rule<Iterator, std::string()> reg_name;           // = 1 * (unreserved | escaped | '$' | ',' | ';' | ':' | '@' | '&' | '=' | '+')
      qi::rule<Iterator, std::string()> query;              // = *uric
      qi::rule<Iterator, std::string()> SIP_Version;        // = 'SIP' '|' 1 * DIGIT '.' 1 * DIGIT

      qi::rule<Iterator, std::string()> message_header;     // = (Accept | Accept_Encoding | Accept_Language | Alert_Info | Allow | Authentication_Info | Authorization | Call_ID | Call_Info | Contact | Content_Disposition | Content_Encoding | Content_Language | Content_Length | Content_Type | CSeq | Date | Error_Info | Expires | From | In_Reply_To | Max_Forwards | MIME_Version | Min_Expires | Organization | Priority | Proxy_Authenticate | Proxy_Authorization | Proxy_Require | Record_Route | Reply_To | Require | Retry_After | Route | Server | Subject | Supported | Timestamp | To | Unsupported | User_Agent | Via | Warning | WWW_Authenticate | extension_header) CRLF

      qi::rule<Iterator, std::string()> Method;            //=  INVITEm / ACKm / OPTIONSm / BYEm / CANCELm / REGISTERm / extension-method
      qi::rule<Iterator, std::string()> extension_method;  //=  token
      qi::rule<Iterator, std::string()> Response;          //=  Status-Line *( message-header ) CRLF [ message-body ]

      qi::rule<Iterator, std::string()> Status_Line;       //=  SIP-Version SP Status-Code SP Reason-Phrase CRLF
      qi::rule<Iterator, std::string()> Status_Code;       //=  Informational /   Redirection /   Success /   Client-Error /   Server-Error /   Global-Failure /   extension-code
      //
      qi::rule<Iterator, std::string()> extension_code;    //=  3DIGIT
      qi::rule<Iterator, std::string()> Reason_Phrase;     //=  *(reserved / unreserved / escaped / UTF8-NONASCII / UTF8-CONT / SP / HTAB)

      qi::rule<Iterator, std::string()> Informational;     //  =  "100"/   "180" /   "181" /   "182" /   "183"
      qi::rule<Iterator, std::string()> Success;           // =  "200" 
      qi::rule<Iterator, std::string()> Redirection;       //=  "300" /   "301" /   "302" /   "305" /   "380"
      qi::rule<Iterator, std::string()> Client_Error;      // =  "400" /   "401" /   "402" /   "403" /   "404" /   "405" /   "406" /   "407" /   "408" /   "410" /   "413" /   "414" /   "415" /   "416" /   "420" /   "421" /   "423" /   "480" /   "481" /   "482" /   "483" /   "484" /   "485" /   "486" /   "487" /   "488" /   "491" /   "493"
      qi::rule<Iterator, std::string()> Server_Error;      // =  "500" /   "501" /   "502" /   "503" /   "504" /   "505" /   "513"
      qi::rule<Iterator, std::string()> Global_Failure;    //=  "600"  ;  Busy Everywhere /   "603"  ;  Decline /   "604"  ;  Does not exist anywhere /   "606"  ;  Not Acceptable
      qi::rule<Iterator, std::string()> Accept;            //=  "Accept" HCOLON [ accept-range *(COMMA accept-range) ]
      qi::rule<Iterator, std::string()> accept_range;      //=  media-range *(SEMI accept-param)




      qi::rule<Iterator, std::string()> media_range;    //=  ( "*|*" | ( m_type SLASH "*" ) | ( m_type SLASH m_subtype )) *( SEMI m_parameter )
      qi::rule<Iterator, std::string()> accept_param;   //=  ("q" EQUAL qvalue) | generic_param
      qi::rule<Iterator, std::string()> qvalue;         //=  ( "0" [ "." 0*3DIGIT ] ) | ( "1" [ "." 0*3("0") ] )
      qi::rule<Iterator, std::string()> generic_param;  //=  token [ EQUAL gen_value ]
      qi::rule<Iterator, std::string()> gen_value;      //=  token | host | quoted_string

      qi::rule<Iterator, std::string()> Accept_Encoding;  //=  "Accept_Encoding" HCOLON [ encoding *(COMMA encoding) ]
      qi::rule<Iterator, std::string()> encoding;         //=  codings *(SEMI accept_param)
      qi::rule<Iterator, std::string()> codings;          //=  content_coding | "*"
      qi::rule<Iterator, std::string()> content_coding;   //=  token

      qi::rule<Iterator, std::string()> Accept_Language;    //=  "Accept_Language" HCOLON [ language *(COMMA language) ]
      qi::rule<Iterator, std::string()> language;           //=  language_range *(SEMI accept_param)
      qi::rule<Iterator, std::string()> language_range;     //=  ( ( 1*8ALPHA *( "_" 1*8ALPHA ) ) | "*" )
      qi::rule<Iterator, std::string()> Alert_Info;         //=  "Alert_Info" HCOLON alert_param *(COMMA alert_param)
      qi::rule<Iterator, std::string()> alert_param;        //=  LAQUOT absoluteURI RAQUOT *( SEMI generic_param )

      qi::rule<Iterator, std::string()> Allow;              //= "Allow" HCOLON[Method *(COMMA Method)]

      qi::rule<Iterator, std::string()> Authorization;      //=  "Authorization" HCOLON credentials
      qi::rule<Iterator, std::string()> credentials;        //=  ("Digest" LWS digest_response) | other_response
      qi::rule<Iterator, std::string()> digest_response;    //=  dig_resp *(COMMA dig_resp)
      qi::rule<Iterator, std::string()> dig_resp;           //=  username | realm | nonce | digest_uri | dresponse | algorithm | cnonce | opaque | message_qop | nonce_count | auth_param
      qi::rule<Iterator, std::string()> username;           //=  "username" EQUAL username_value
      qi::rule<Iterator, std::string()> username_value;     //=  quoted_string
      qi::rule<Iterator, std::string()> digest_uri;         //=  "uri" EQUAL LDQUOT digest_uri_value RDQUOT
      qi::rule<Iterator, std::string()> digest_uri_value;   //=  rquest_uri ; Equal to request_uri as specified by HTTP|1.1
      qi::rule<Iterator, std::string()> message_qop;        //=  "qop" EQUAL qop_value

      qi::rule<Iterator, std::string()> cnonce;            //=  "cnonce" EQUAL cnonce_value
      qi::rule<Iterator, std::string()> cnonce_value;      //=  nonce_value
      qi::rule<Iterator, std::string()> nonce_count;      //=  "nc" EQUAL nc_value
      qi::rule<Iterator, std::string()> nc_value;    //=  8LHEX
      qi::rule<Iterator, std::string()> dresponse;  //=  "response" EQUAL request_digest
      qi::rule<Iterator, std::string()> request_digest;  //=  LDQUOT 32LHEX RDQUOT
      qi::rule<Iterator, std::string()> auth_param;  //=  auth_param_name EQUAL ( token | quoted_string )
      qi::rule<Iterator, std::string()> auth_param_name;  //=  token
      qi::rule<Iterator, std::string()> other_response; //=  auth_scheme LWS auth_param *(COMMA auth_param)
      qi::rule<Iterator, std::string()> auth_scheme;  //=  token

      qi::rule<Iterator, std::string()> Authentication_Info; //=  "Authentication_Info" HCOLON ainfo *(COMMA ainfo)
      qi::rule<Iterator, std::string()> ainfo;   //=  nextnonce | message_qop | response_auth | cnonce | nonce_count
      qi::rule<Iterator, std::string()> nextnonce;   //=  "nextnonce" EQUAL nonce_value
      qi::rule<Iterator, std::string()> response_auth;   //=  "rspauth" EQUAL response_digest
      qi::rule<Iterator, std::string()> response_digest;   //=  LDQUOT *LHEX RDQUOT

      qi::rule<Iterator, std::string()> Call_ID; //=  ( "Call_ID" | "i" ) HCOLON callid
      qi::rule<Iterator, std::string()> callid; //=  word [ "@" word ]

      qi::rule<Iterator, std::string()> Call_Info; //=  "Call_Info" HCOLON info *(COMMA info)
      qi::rule<Iterator, std::string()> info; //=  LAQUOT absoluteURI RAQUOT *( SEMI info_param)
      qi::rule<Iterator, std::string()> info_param;//=  ( "purpose" EQUAL ( "icon" | "info" | "card" | token ) ) | generic_param

      qi::rule<Iterator, std::string()> Contact;   //=  ("Contact" | "m" ) HCOLON ( STAR | (contact_param *(COMMA contact_param)))
      qi::rule<Iterator, std::string()> contact_param; //=  (name_addr | addr_spec) *(SEMI contact_params)
      qi::rule<Iterator, std::string()> name_addr;   //=  [ display_name ] LAQUOT addr_spec RAQUOT
      qi::rule<Iterator, std::string()> addr_spec;   //=  SIP_URI | SIPS_URI | absoluteURI
      qi::rule<Iterator, std::string()> display_name;  //=  *(token LWS)| quoted_string

      qi::rule<Iterator, std::string()> contact_params;   //=  c_p_q | c_p_expires | contact_extension
      qi::rule<Iterator, std::string()> c_p_q;    //=  "q" EQUAL qvalue
      qi::rule<Iterator, std::string()> c_p_expires;    //=  "expires" EQUAL delta_seconds
      qi::rule<Iterator, std::string()> contact_extension;  //=  generic_param
      qi::rule<Iterator, std::string()> delta_seconds;   //=  1*DIGIT

      qi::rule<Iterator, std::string()> Content_Disposition;  //=  "Content_Disposition" HCOLON disp_type *( SEMI disp_param )
      qi::rule<Iterator, std::string()> disp_type;   //=  "render" | "session" | "icon" | "alert" | disp_extension_token

      qi::rule<Iterator, std::string()> disp_param;    //=  handling_param | generic_param
      qi::rule<Iterator, std::string()> handling_param;    //=  "handling" EQUAL ( "optional" | "required" | other_handling )
      qi::rule<Iterator, std::string()> other_handling;    //=  token
      qi::rule<Iterator, std::string()> disp_extension_token;  //=  token

      qi::rule<Iterator, std::string()> Content_Encoding;

      qi::rule<Iterator, std::string()> Content_Language;
      qi::rule<Iterator, std::string()> language_tag;   //
      qi::rule<Iterator, std::string()> primary_tag;    //
      qi::rule<Iterator, std::string()> subtag;   //=  1*8

      qi::rule<Iterator, std::string()> Content_Length;
      qi::rule<Iterator, std::string()> Content_Type;   //
      qi::rule<Iterator, std::string()> media_type; //=  m
      qi::rule<Iterator, std::string()> m_type;   //=  dis
      qi::rule<Iterator, std::string()> discrete_type;  //
      qi::rule<Iterator, std::string()> composite_type;
      qi::rule<Iterator, std::string()> extension_token;
      qi::rule<Iterator, std::string()> ietf_token;
      qi::rule<Iterator, std::string()> x_token;
      qi::rule<Iterator, std::string()> m_subtype;
      qi::rule<Iterator, std::string()> iana_token;
      qi::rule<Iterator, std::string()> m_parameter;
      qi::rule<Iterator, std::string()> m_attribute;
      qi::rule<Iterator, std::string()> m_value;

      qi::rule<Iterator, std::string()> CSeq;

      qi::rule<Iterator, std::string()> Date;
      qi::rule<Iterator, std::string()> SIP_date;
      qi::rule<Iterator, std::string()> rfc1123_date;
      qi::rule<Iterator, std::string()> date1;
      qi::rule<Iterator, std::string()> time;
      qi::rule<Iterator, std::string()> wkday;
      qi::rule<Iterator, std::string()> month;

      qi::rule<Iterator, std::string()> Error_Info;

      qi::rule<Iterator, std::string()> error_uri;

      qi::rule<Iterator, std::string()> Expires;
      qi::rule<Iterator, std::string()> From;
      qi::rule<Iterator, std::string()> from_spec;
      qi::rule<Iterator, std::string()> from_param;
      qi::rule<Iterator, std::string()> tag_param;

      qi::rule<Iterator, std::string()> In_Reply_To;

      qi::rule<Iterator, std::string()> Max_Forwards;

      qi::rule<Iterator, std::string()> MIME_Version;

      qi::rule<Iterator, std::string()> Min_Expires;

      qi::rule<Iterator, std::string()> Organization;

      qi::rule<Iterator, std::string()> Priority;
      qi::rule<Iterator, std::string()> priority_value;
      qi::rule<Iterator, std::string()> other_priority;

      qi::rule<Iterator, std::string()> Proxy_Authenticate; 
      qi::rule<Iterator, std::string()> challenge;    
      qi::rule<Iterator, std::string()> other_challenge;
      qi::rule<Iterator, std::string()> digest_cln;
      qi::rule<Iterator, std::string()> realm;
      qi::rule<Iterator, std::string()> realm_value;
      qi::rule<Iterator, std::string()> domain;     
      qi::rule<Iterator, std::string()> URI;   
      qi::rule<Iterator, std::string()> nonce;   
      qi::rule<Iterator, std::string()> nonce_value;
      qi::rule<Iterator, std::string()> opaque;     
      qi::rule<Iterator, std::string()> stale;
      qi::rule<Iterator, std::string()> algorithm;  
      qi::rule<Iterator, std::string()> qop_options;
      qi::rule<Iterator, std::string()> qop_value;

      qi::rule<Iterator, std::string()> Proxy_Authorization;

      qi::rule<Iterator, std::string()> Proxy_Require;
      qi::rule<Iterator, std::string()> option_tag;   

      qi::rule<Iterator, std::string()> Record_Route; 
      qi::rule<Iterator, std::string()> rec_route;    
      qi::rule<Iterator, std::string()> rr_param;     

      qi::rule<Iterator, std::string()> Reply_To;     
      qi::rule<Iterator, std::string()> rplyto_spec;
      qi::rule<Iterator, std::string()> rplyto_param; 
      qi::rule<Iterator, std::string()> Require;    

      qi::rule<Iterator, std::string()> Retry_After;

      qi::rule<Iterator, std::string()> retry_param;

      qi::rule<Iterator, std::string()> Route;
      qi::rule<Iterator, std::string()> route_param;

      qi::rule<Iterator, std::string()> Server;
      qi::rule<Iterator, std::string()> server_val;
      qi::rule<Iterator, std::string()> product;
      qi::rule<Iterator, std::string()> product_version; 

      qi::rule<Iterator, std::string()> Subject;  

      qi::rule<Iterator, std::string()> Supported;
      qi::rule<Iterator, std::string()> Timestamp;
      qi::rule<Iterator, std::string()> delay;    
      qi::rule<Iterator, std::string()> To;
      qi::rule<Iterator, std::string()> to_param; 
      qi::rule<Iterator, std::string()> Unsupported;
      qi::rule<Iterator, std::string()> User_Agent;

      qi::rule<Iterator, std::string()> Via;       
      qi::rule<Iterator, std::string()> via_parm;  
      qi::rule<Iterator, std::string()> via_params;
      qi::rule<Iterator, std::string()> via_ttl;   
      qi::rule<Iterator, std::string()> via_maddr; 
      qi::rule<Iterator, std::string()> via_received;
      qi::rule<Iterator, std::string()> via_branch;
      qi::rule<Iterator, std::string()> via_extension;
      qi::rule<Iterator, std::string()> sent_protocol;
      qi::rule<Iterator, std::string()> protocol_name;
      qi::rule<Iterator, std::string()> protocol_version;
      qi::rule<Iterator, std::string()> transport;
      qi::rule<Iterator, std::string()> sent_by;  
      qi::rule<Iterator, std::string()> ttl;

      qi::rule<Iterator, std::string()> Warning;
      qi::rule<Iterator, std::string()> warning_value;
      qi::rule<Iterator, std::string()> warn_code;
      qi::rule<Iterator, std::string()> warn_agent;

      qi::rule<Iterator, std::string()> warn_text;
      qi::rule<Iterator, std::string()> pseudonym;
      qi::rule<Iterator, std::string()> WWW_Authenticate;
      qi::rule<Iterator, std::string()> extension_header;
      qi::rule<Iterator, std::string()> header_name;
      qi::rule<Iterator, std::string()> header_value;
      qi::rule<Iterator, std::string()> message_body;


      SIPGrammar(void);
    };
  }
}

#endif // SIP0X_PARSER_SIPGRAMMAR_HPP__

#endif