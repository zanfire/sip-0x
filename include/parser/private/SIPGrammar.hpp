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
    using ascii::char_;;
    using qi::on_error;
    using qi::fail;
    using ascii::char_;
    using namespace qi::labels;

    using phoenix::construct;
    using phoenix::val;
 

    template <typename Iterator>
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

      qi::rule<Iterator, std::string()> STAR;   //=  SWS "*" SWS ; asterisk
      qi::rule<Iterator, std::string()> SLASH;  //=  SWS "/" SWS ; slash
      qi::rule<Iterator, std::string()> EQUAL;  //=  SWS "=" SWS ; equal
      qi::rule<Iterator, std::string()> LPAREN; //=  SWS "(" SWS ; left parenthesis
      qi::rule<Iterator, std::string()> RPAREN; //=  SWS ")" SWS ; right parenthesis
      qi::rule<Iterator, std::string()> RAQUOT; //=  ">" SWS ; right angle quote
      qi::rule<Iterator, std::string()> LAQUOT; //=  SWS "<"; left angle quote
      qi::rule<Iterator, std::string()> COMMA;  //=  SWS "," SWS ; comma
      qi::rule<Iterator, std::string()> SEMI;   //=  SWS ";" SWS ; semicolon
      qi::rule<Iterator, std::string()> COLON;  //=  SWS ":" SWS ; colon
      qi::rule<Iterator, std::string()> LDQUOT; //=  SWS DQUOTE; open double quotation mark
      qi::rule<Iterator, std::string()> RDQUOT; //=  DQUOTE SWS ; close double quotation mark

      qi::rule<Iterator, std::string()> HCOLON;

      qi::rule<Iterator, std::string()> TEXT_UTF8_TRIM; //= 1 * TEXT - UTF8char *(*LWS TEXT - UTF8char)
      qi::rule<Iterator, std::string()> TEXT_UTF8char;  //= %x21 - 7E / UTF8 - NONASCII
      qi::rule<Iterator, std::string()> UTF8_NONASCII;  //= %xC0 - DF 1UTF8 - CONT / %xE0 - EF 2UTF8 - CONT / %xF0 - F7 3UTF8 - CONT / %xF8 - Fb 4UTF8 - CONT / %xFC - FD 5UTF8 - CONT
      qi::rule<Iterator, std::string()> UTF8_CONT;      //= %x80 - BF

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
    
      qi::rule<Iterator, std::string()> Proxy_Authenticate;   //=  "Proxy_Authenticate" HCOLON challenge
      qi::rule<Iterator, std::string()> challenge;    //=  ("Digest" LWS digest_cln *(COMMA digest_cln)) | other_challenge
      qi::rule<Iterator, std::string()> other_challenge;    //=  auth_scheme LWS auth_param *(COMMA auth_param)
      qi::rule<Iterator, std::string()> digest_cln;     //=  realm | domain | nonce | opaque | stale | algorithm | qop_options | auth_param
      qi::rule<Iterator, std::string()> realm;     //=  "realm" EQUAL realm_value
      qi::rule<Iterator, std::string()> realm_value;     //=  quoted_string
      qi::rule<Iterator, std::string()> domain;     //=  "domain" EQUAL LDQUOT URI *( 1*SP URI ) RDQUOT
      qi::rule<Iterator, std::string()> URI;     //=  absoluteURI | abs_path
      qi::rule<Iterator, std::string()> nonce;     //=  "nonce" EQUAL nonce_value
      qi::rule<Iterator, std::string()> nonce_value;     //=  quoted_string
      qi::rule<Iterator, std::string()> opaque;     //=  "opaque" EQUAL quoted_string
      qi::rule<Iterator, std::string()> stale;    //=  "stale" EQUAL ( "true" | "false" )
      qi::rule<Iterator, std::string()> algorithm;       //=  "algorithm" EQUAL ( "MD5" | "MD5_sess" | token )
      qi::rule<Iterator, std::string()> qop_options;      //=  "qop" EQUAL LDQUOT qop_value *("," qop_value) RDQUOT
      qi::rule<Iterator, std::string()> qop_value;     //=  "auth" | "auth_int" | token
    
      qi::rule<Iterator, std::string()> Proxy_Authorization; //=  "Proxy_Authorization" HCOLON credentials
    
      qi::rule<Iterator, std::string()> Proxy_Require;     //=  "Proxy_Require" HCOLON option_tag *(COMMA option_tag)
      qi::rule<Iterator, std::string()> option_tag;    //=  token
    
      qi::rule<Iterator, std::string()> Record_Route;    //=  "Record_Route" HCOLON rec_route *(COMMA rec_route)
      qi::rule<Iterator, std::string()> rec_route;       //=  name_addr *( SEMI rr_param )
      qi::rule<Iterator, std::string()> rr_param;       //=  generic_param
    
      qi::rule<Iterator, std::string()> Reply_To;      //=  "Reply_To" HCOLON rplyto_spec
      qi::rule<Iterator, std::string()> rplyto_spec;     //=  ( name_addr | addr_spec ) *( SEMI rplyto_param )
      qi::rule<Iterator, std::string()> rplyto_param;    //=  generic_param
      qi::rule<Iterator, std::string()> Require;    //=  "Require" HCOLON option_tag *(COMMA option_tag)
    
      qi::rule<Iterator, std::string()> Retry_After;     //=  "Retry_After" HCOLON delta_seconds [ comment ] *( SEMI retry_param )
    
      qi::rule<Iterator, std::string()> retry_param;    //=  ("duration" EQUAL delta_seconds) | generic_param
    
      qi::rule<Iterator, std::string()> Route;    //=  "Route" HCOLON route_param *(COMMA route_param)
      qi::rule<Iterator, std::string()> route_param;    //=  name_addr *( SEMI rr_param )
     
      qi::rule<Iterator, std::string()> Server;     //=  "Server" HCOLON server_val *(LWS server_val)
      qi::rule<Iterator, std::string()> server_val;    //=  product | comment
      qi::rule<Iterator, std::string()> product;    //=  token [SLASH product_version]
      qi::rule<Iterator, std::string()> product_version;   //=  token
     
      qi::rule<Iterator, std::string()> Subject;     //=  ( "Subject" | "s" ) HCOLON [TEXT_UTF8_TRIM]
    
      qi::rule<Iterator, std::string()> Supported;     //=  ( "Supported" | "k" ) HCOLON [option_tag *(COMMA option_tag)]
      qi::rule<Iterator, std::string()> Timestamp;     //=  "Timestamp" HCOLON 1*(DIGIT) [ "." *(DIGIT) ] [ LWS delay ]
      qi::rule<Iterator, std::string()> delay;     //=  *(DIGIT) [ "." *(DIGIT) ]
      qi::rule<Iterator, std::string()> To;    //=  ( "To" | "t" ) HCOLON ( name_addr | addr_spec ) *( SEMI to_param )
      qi::rule<Iterator, std::string()> to_param;   //=  tag_param | generic_param
      qi::rule<Iterator, std::string()> Unsupported;    //=  "Unsupported" HCOLON option_tag *(COMMA option_tag)
      qi::rule<Iterator, std::string()> User_Agent;   //=  "User_Agent" HCOLON server_val *(LWS server_val)
    
      qi::rule<Iterator, std::string()> Via;       //=  ( "Via" | "v" ) HCOLON via_parm *(COMMA via_parm)
      qi::rule<Iterator, std::string()> via_parm;       //=  sent_protocol LWS sent_by *( SEMI via_params )
      qi::rule<Iterator, std::string()> via_params;     //=  via_ttl | via_maddr | via_received | via_branch | via_extension
      qi::rule<Iterator, std::string()> via_ttl;     //=  "ttl" EQUAL ttl
      qi::rule<Iterator, std::string()> via_maddr;    //=  "maddr" EQUAL host
      qi::rule<Iterator, std::string()> via_received;    //=  "received" EQUAL (IPv4address | IPv6address)
      qi::rule<Iterator, std::string()> via_branch;    //=  "branch" EQUAL token
      qi::rule<Iterator, std::string()> via_extension;    //=  generic_param
      qi::rule<Iterator, std::string()> sent_protocol;    //=  protocol_name SLASH protocol_version SLASH transport
      qi::rule<Iterator, std::string()> protocol_name;    //=  "SIP" | token
      qi::rule<Iterator, std::string()> protocol_version;    //=  token
      qi::rule<Iterator, std::string()> transport;      //=  "UDP" | "TCP" | "TLS" | "SCTP" | other_transport
      qi::rule<Iterator, std::string()> sent_by;      //=  host [ COLON port ]
      qi::rule<Iterator, std::string()> ttl;      //=  1*3DIGIT ; 0 to 255
    
      qi::rule<Iterator, std::string()> Warning;      //=  "Warning" HCOLON warning_value *(COMMA warning_value)
      qi::rule<Iterator, std::string()> warning_value;      //=  warn_code SP warn_agent SP warn_text
      qi::rule<Iterator, std::string()> warn_code;      //=  3DIGIT
      qi::rule<Iterator, std::string()> warn_agent;      //=  hostport | pseudonym
    
      qi::rule<Iterator, std::string()> warn_text;       //=  quoted_string
      qi::rule<Iterator, std::string()> pseudonym;       //=  token
      qi::rule<Iterator, std::string()> WWW_Authenticate;    //=  "WWW_Authenticate" HCOLON challenge
      qi::rule<Iterator, std::string()> extension_header;    //=  header_name HCOLON header_value
      qi::rule<Iterator, std::string()> header_name;    //=  token
      qi::rule<Iterator, std::string()> header_value;    //=  *(TEXT_UTF8char | UTF8_CONT | LWS)
      qi::rule<Iterator, std::string()> message_body;    //=  *OCTET


      SIPGrammar() : SIPGrammar::base_type(root)
      {
        // Initialization 
        // Core rules
        CRLF.name("CRLF");
        CRLF = lit("\r\n");
        SP.name("SP");
        SP = char_(' ');
        ALPHA = char_("A-Z") | char_("a-z");
        DIGIT = char_("0-9");
        HEXDIG = DIGIT | char_("A-F");
        LWSP = *((WSP | CRLF) >> WSP); // linear white space(past newline)
        OCTET = char_(0x00, 0xFF); // 8 bits of data
        VCHAR = char_(0x21, 0x7E); // visible(printing) characters
        WSP.name("WSP");
        WSP = SP | char_(0x09); // white space
        HTAB = char_(0x09);
        DQUOTE = char_(0x22);

        // Basic rules
        alphanum = ALPHA | DIGIT;

        reserved = char_(';') | char_('|') | char_('?') | char_(':') | char_('@') | char_('&') | char_('=') | char_('+') | char_('$') | char_(',');
        mark = char_('-') | char_('_') | char_('.') | char_('!') | char_('~') | char_('*') | char_('\'') | char_('(') | char_(')');
        unreserved = alphanum | mark;
        escaped = char_('%') > HEXDIG > HEXDIG;

        LWS.name("LWS");
        LWS = -(*WSP >> CRLF) >> +WSP; // linear whitespace
        SWS.name("SWS");
        SWS = -LWS;

        STAR = SWS >> '*' >> SWS;
        SLASH = SWS >> '/' >> SWS;
        EQUAL = SWS >> '=' >> SWS;
        LPAREN = SWS >> '(' >> SWS;
        RPAREN = SWS >> ')' >> SWS;
        RAQUOT = '>' >> SWS;
        LAQUOT = SWS >> '<';
        COMMA = SWS >> ',' >> SWS;
        SEMI = SWS >> ';' >> SWS;
        COLON.name("COLON");
        COLON = SWS >> ':' >> SWS;
        LDQUOT = SWS >> DQUOTE;
        RDQUOT = DQUOTE >> SWS;

        HCOLON.name("HCOLON");
        HCOLON = *(WSP) >> char_(':') >> SWS;

        TEXT_UTF8_TRIM = +TEXT_UTF8char > *(*LWS > TEXT_UTF8char);
        TEXT_UTF8char = char_(0x21, 0x7E) | UTF8_NONASCII;
        UTF8_NONASCII = (char_(0xC0, 0xDF) > UTF8_CONT) | (char_(0xE0, 0xEF) > repeat(2, 2)[UTF8_CONT]) | (char_(0xF0, 0xF7) > repeat(3, 3)[UTF8_CONT]) | (char_(0xF8, 0xFb) > repeat(4, 4)[UTF8_CONT]) | (char_(0xFC, 0xFD) > repeat(5, 5)[UTF8_CONT]);
        UTF8_CONT = char_(0x80, 0xBF);

        LHEX = DIGIT | char_("a-f");

        token = +(alphanum | '-' | '.' | '!' | '%' | '*' | '_' | '+' | '`' | '\'' | '~');
        separators = (char_('(') | char_(')') | char_('<') | char_('>') | char_('@') | char_(',') | char_(';') | char_(':') | char_('\\') | char_('\"') | char_('|') | char_('[') | char_(']') | char_('?') | char_('=') | char_('{') | char_('}') | SP | HTAB);
        word = +(alphanum | '-' | '.' | '!' | '%' | '*' | '_' | '+' | '`' | '\'' | '~' | '(' | ')' | '<' | '>' | ':' | '\\' | '\"' | '|' | '[' | ']' | '?' | '{' | '}');

        comment = LPAREN > *(ctext | quoted_pair | comment) > RPAREN;
        ctext = (char_(0x21, 0x27) | char_(0x2A, 0x5B) | char_(0x5D, 0x7E)) > UTF8_NONASCII | LWS;

        quoted_string = SWS > DQUOTE > *(qdtext | quoted_pair) > DQUOTE;
        qdtext = LWS | char_(0x21) | char_(0x23, 0x5B) | char_(0x5D, 0x7E) | UTF8_NONASCII;

        quoted_pair = '\"' > (char_(0x00, 0x09) | char_(0x0B, 0x0C) | char_(0x0E, 0x7F));

        nonce_value = quoted_string;

        // TODO: COLLAPS in one rules ??
        SIP_URI = lit("sip:") > -userinfo > hostport >> uri_parameters >> -headers;
        SIPS_URI = lit("sips:") > -userinfo > hostport >> uri_parameters >> -headers;
        // TELEPHONE_SUBSCRIBER is in RFC 2806
        domainlabel.name("domainlabel");
        domainlabel = alphanum >> *(alphanum | lit("-")) >> alphanum;
        //domainlabel = alphanum | (alphanum >> *(alphanum | lit("-")) >> alphanum);
        toplabel.name("toplabel");
        //toplabel = ALPHA | (ALPHA >> *(alphanum | lit("-")) >> alphanum);
        toplabel = ALPHA >> *(alphanum | lit("-")) >> alphanum;
        hostname.name("hostname");
        //hostname = *(domainlabel > char_('.')) > toplabel > -char_('.');
        hostname = *(*alphanum >> char_('.')) >> *alphanum >> -char_('.');
        host.name("host");
        host = hostname | IPv4address | IPv6reference;
        userinfo.name("userinfo");
        userinfo = user /*(| telephone_subscriber)*/ >> -(char_(':') >> password) >> char_('@');
        user = +(unreserved | escaped | user_unreserved);
        user_unreserved = char_('&') | char_('=') | char_('+') | char_('$') | char_(',') | char_(';') | char_('?') | char_('|');
        password.name("password");
        password = *(unreserved | escaped | char_('&') | char_('=') | char_('+') | char_('$') | char_(','));
        hostport.name("hostport");
        hostport = host > -(char_(':') > port);
        IPv4address.name("IPv4Address");
        IPv4address = +DIGIT >> char_('.') >> qi::repeat(1, 3)[DIGIT] >> char_('.') >> qi::repeat(1, 3)[DIGIT] > char_('.') > qi::repeat(1, 3)[DIGIT];
        IPv6reference.name("IPv6reference");
        IPv6reference = char_('[') > IPv6address > char_(']');
        IPv6address.name("IPv6address");
        IPv6address = hexpart > -(char_(':') > IPv4address);
        hexpart.name("hexpart");
        hexpart = hexseq | (hexseq > lit("::") > -hexseq) | (lit("::") > -hexseq);
        hexseq.name("hexseq");
        hexseq = hex4 > *(char_(':') > hex4);
        hex4 = qi::repeat(1, 4)[HEXDIG];
        port.name("port");
        port = +DIGIT;

        uri_parameters.name("uri_parameters");
        uri_parameters = *(char_(';') >> uri_parameter);
        uri_parameter.name("uri_parameter");
        uri_parameter = transport_param | user_param | method_param | ttl_param | maddr_param | lr_param | other_param;
        transport_param = lit("transport=") > (lit("udp") | lit("tcp") | lit("sctp") | lit("tls") | other_transport);
        other_transport = token;
        user_param = lit("user=") > (lit("phone") | lit("ip") | other_user);
        other_user = token;
        method_param = lit("method=") > Method;
        ttl_param = lit("ttl=") >> ttl;
        maddr_param = lit("maddr=") > host;
        lr_param = lit("lr");
        other_param = pname > -(char_('=') > pvalue);
        pname = +paramchar;
        pvalue = +paramchar;
        paramchar = param_unreserved | unreserved | escaped;
        param_unreserved = char_('[') | char_(']') | char_('|') | char_(':') | char_('&') | char_('+') | char_('$');

        headers.name("headers");
        headers = char_('?') > header > *(char_('&') > header);
        header.name("header");
        header = hname > char_('=') > hvalue;
        hname = +(hnv_unreserved | unreserved | escaped);
        hvalue = *(hnv_unreserved | unreserved | escaped);
        hnv_unreserved = char_('[') | char_(']') | char_('|') | char_('?') | char_(':') | char_('+') | char_('$');

        SIP_message           = Request | Response;
        Request               = Request_Line > *(message_header) > CRLF > -message_body;
        Request_Line          = Method > SP > RequestURI > SP > SIP_Version > CRLF;
        RequestURI            = SIP_URI | SIPS_URI | absoluteURI;
        absoluteURI           = scheme > char_(':') > (hier_part | opaque_part);
        hier_part             = (net_path | abs_path) > -(char_('?') > query);
        net_path              = lit("||") > authority > -abs_path;
        abs_path              = char_('|') > path_segments;

        opaque_part           = uric_no_slash > *uric;
        uric                  = reserved | unreserved | escaped;
        uric_no_slash         = unreserved | escaped | char_(';') | char_('?') | char_(':') | char_('@') | char_('&') | char_('=') | char_('+') | char_('$') | char_(',');
        path_segments         = segment > *(char_('|') > segment);
        segment               = *pchar > *(char_(';') > param);
        param                 = *pchar;
        pchar                 = unreserved | escaped | char_(':') | char_('@') | char_('&') | char_('=') | char_('+') | char_('$') | char_(',');
        scheme                = ALPHA > *(ALPHA | DIGIT | lit("+") | lit("-") | lit("."));
        authority             = srvr | reg_name;
        srvr                  = -(-(userinfo > char_('@')) > hostport);
        reg_name              = +(unreserved | escaped | char_('$') | char_(',') | char_(';') | char_(':') | char_('@') | char_('&') | char_('=') | char_('+'));
        query                 = *uric;
        SIP_Version           = lit("SIP") > char_('/') >  +DIGIT > char_('.') > +DIGIT;

        message_header.name("message-header");
        message_header        = (Accept | Accept_Encoding | Accept_Language | Alert_Info | Allow | Authentication_Info | Authorization | Call_ID | Call_Info | Contact | Content_Disposition | Content_Encoding | Content_Language | Content_Length | Content_Type | CSeq | Date | Error_Info | Expires | From | In_Reply_To | Max_Forwards | MIME_Version | Min_Expires | Organization | Priority | Proxy_Authenticate | Proxy_Authorization | Proxy_Require | Record_Route | Reply_To | Require | Retry_After | Route | Server | Subject | Supported | Timestamp | To | Unsupported | User_Agent | Via | Warning | WWW_Authenticate | extension_header) >> CRLF;

        Method                = lit("INVITE") | lit("ACK") | lit("OPTIONS") | lit("BYE") | lit("CANCEL") | lit("REGISTER") | extension_method;
        extension_method      = token;
        Response              = Status_Line > *(message_header) > CRLF > -message_body;

        Status_Line           = SIP_Version > SP > Status_Code > SP > Reason_Phrase > CRLF;
        Status_Code           = Informational | Redirection | Success | Client_Error | Server_Error | Global_Failure | extension_code;

        extension_code        = qi::repeat(3, 3)[DIGIT];
        Reason_Phrase         = *(reserved | unreserved | escaped | UTF8_NONASCII | UTF8_CONT | SP | HTAB);

        Informational         = lit("100") | lit("180") | lit("181") | lit("182") | lit("183");
        Success               = lit("200");
        Redirection           = lit("300") | lit("301") | lit("302") | lit("305") | lit("380");
        Client_Error          = lit("400") | lit("401") | lit("402") | lit("403") | lit("404") | lit("405") | lit("406") | lit("407") | lit("408") | lit("410") | lit("413") | lit("414") | lit("415") | lit("416") | lit("420") | lit("421") | lit("423") | lit("480") | lit("481") | lit("482") | lit("483") | lit("484") | lit("485") | lit("486") | lit("487") | lit("488") | lit("491") | lit("493");
        Server_Error          = lit("500") | lit("501") | lit("502") | lit("503") | lit("504") | lit("505") | lit("513");
        Global_Failure        = lit("600") | lit("603") | lit("604") | lit("606");
        Accept                = lit("Accept") > HCOLON > -(accept_range > *(COMMA > accept_range));
        accept_range          = media_range > *(SEMI > accept_param);

        //media_range           = (lit("*/*") | (m_type > SLASH > lit("*")) | (m_type > SLASH > m_subtype)) > *(SEMI > m_parameter);
        accept_param          = (char_('q') > EQUAL > qvalue) | generic_param;
        qvalue                = (char_('0') > -(char_('.') > repeat(0, 3)[DIGIT])) | (char_('1') > -(char_('.') > repeat(0, 3)[char_('0')]));
        generic_param         = token > -(EQUAL > gen_value);
        gen_value             = token | host | quoted_string;

        Accept_Encoding       =  lit("Accept-Encoding") > HCOLON > -(encoding > *(COMMA > encoding));
        encoding              =  codings > *(SEMI > accept_param);
        codings               =  content_coding | char_('*');
        content_coding        =  token;

        Accept_Language       =  lit("Accept-Language") > HCOLON > -(language > *(COMMA > language));
        language              =  language_range > *(SEMI > accept_param);
        language_range        = ((repeat(1, 8)[ALPHA] >>*( char_('_') > repeat(1, 8)[ALPHA])) | "*");
        Alert_Info            =  lit("Alert-Info") > HCOLON > alert_param > *(COMMA > alert_param);
        alert_param           =  LAQUOT > absoluteURI > RAQUOT > *(SEMI > generic_param);

        Allow                 = lit("Allow") > HCOLON > -(Method > *(COMMA > Method));

        Authorization         =  lit("Authorization") > HCOLON > credentials;
        credentials           =  (lit("Digest") > LWS > digest_response) | other_response;
        digest_response       =  dig_resp > *(COMMA > dig_resp);
        dig_resp              =  username | realm | nonce | digest_uri | dresponse | algorithm | cnonce | opaque | message_qop | nonce_count | auth_param;
        username              =  lit("username") > EQUAL > username_value;
        username_value        =  quoted_string;
        digest_uri            =  lit("uri") > EQUAL > LDQUOT > digest_uri_value > RDQUOT;
        
        //digest_uri_value      =  rquest_uri;  // Equal to request_uri as specified by HTTP|1.1
        // TODO: report rquest-uri
        digest_uri_value = token;
        
        message_qop           =  lit("qop") > EQUAL > qop_value;

        cnonce                = lit("cnonce") > EQUAL > cnonce_value;
        cnonce_value          = nonce_value;
        nonce_count           = lit("nc") > EQUAL > nc_value;
        nc_value              = repeat(8,8)[LHEX];
        dresponse             = lit("response") > EQUAL > request_digest;
        request_digest        = LDQUOT > repeat(32, 32)[LHEX] > RDQUOT;
        auth_param            = auth_param_name > EQUAL > (token | quoted_string);
        auth_param_name       = token;
        other_response        = auth_scheme > LWS > auth_param > *(COMMA > auth_param);
        auth_scheme           = token;

        Authentication_Info   = lit("Authentication-Info") > HCOLON > ainfo > *(COMMA > ainfo);
        ainfo                 = nextnonce | message_qop | response_auth | cnonce | nonce_count;
        nextnonce             = lit("nextnonce") > EQUAL > nonce_value;
        response_auth         = lit("rspauth") > EQUAL > response_digest;
        response_digest       = LDQUOT > *LHEX > RDQUOT;

        Call_ID               = (lit("Call-ID") | char_('i')) > HCOLON > callid;
        callid                = word > -(char_('@') > word);

        Call_Info             = lit("Call-Info") > HCOLON > info > *(COMMA > info);
        info                  = LAQUOT > absoluteURI > RAQUOT > *(SEMI > info_param);
        info_param            = (lit("purpose") > EQUAL > (lit("icon") | lit("info") | lit("card") | token)) | generic_param;
        
        Contact.name("Contact");
        Contact = (lit("Contact") | char_('m')) > HCOLON > (STAR | (contact_param >> *(COMMA >> contact_param)));
        contact_param.name("contact_param");
        contact_param = (name_addr | addr_spec) >> *(SEMI >> contact_params);
        addr_spec.name("addr_spec");
        addr_spec = SIP_URI | SIPS_URI | absoluteURI;
        name_addr.name("");
        name_addr = -display_name > LAQUOT > addr_spec > RAQUOT;
        display_name.name("display_name");
        display_name = *(token > LWS) | quoted_string;

        contact_params = c_p_q | c_p_expires | contact_extension;
        c_p_q = char_('q') > EQUAL > qvalue;
        c_p_expires = lit("expires") > EQUAL > delta_seconds;
        contact_extension = generic_param;
        delta_seconds = repeat(1, 1)[DIGIT];


        Content_Disposition   = lit("Content-Disposition") > HCOLON > disp_type > *(SEMI > disp_param);
        disp_type             = lit("render") | lit("session") | lit("icon") | lit("alert") | disp_extension_token;

        disp_param            = handling_param | generic_param;
        handling_param        = lit("handling") > EQUAL > (lit("optional") | lit("required") | other_handling);
        other_handling        = token;
        disp_extension_token  = token;

        Content_Encoding      = (lit("Content-Encoding") | char_('e')) > HCOLON > content_coding > *(COMMA > content_coding);

        Content_Language      = lit("Content_Language") > HCOLON > language_tag > *(COMMA > language_tag);
        language_tag          = primary_tag > *(char_('_') > subtag);
        primary_tag           = repeat(1,8)[ALPHA];
        subtag                = repeat(1,8)[ALPHA];

        Content_Length.name("Content-Length");
        Content_Length        = (lit("Content-Length") | char_('l')) >> HCOLON >> +DIGIT;
        Content_Type          = (lit("Content-Type") | char_('c') ) > HCOLON > media_type;
        media_type            = m_type > SLASH > m_subtype > *(SEMI > m_parameter);
        m_type                = discrete_type | composite_type;
        discrete_type         = lit("text") | lit("image") | lit("audio") | lit("video") | lit("application") | extension_token;
        composite_type        = lit("message") | lit("multipart") | extension_token;
        extension_token       = ietf_token | x_token;
        ietf_token            = token;
        x_token               = lit("x-") > token;
        m_subtype             = extension_token | iana_token;
        iana_token            = token;
        m_parameter           = m_attribute > EQUAL > m_value;
        m_attribute           = token;
        m_value               = token | quoted_string;

        CSeq                  =  lit("CSeq") > HCOLON > +DIGIT > LWS > Method;

        date1                 = repeat(2, 2)[DIGIT] > SP > month > SP > repeat(4, 4)[DIGIT]; // day month year(e.g., 02 Jun 1982);
        time                  = repeat(2, 2)[DIGIT] > char_(':') > repeat(2, 2)[DIGIT] > char_(':') > repeat(2, 2)[DIGIT]; // 00:00 : 00 - 23 : 59 : 59;
        wkday                 = lit("Mon") | lit("Tue") | lit("Wed") | lit("Thu") | lit("Fri") | lit("Sat") | lit("Sun");
        month                 = lit("Jan") | lit("Feb") | lit("Mar") | lit("Apr") | lit("May") | lit("Jun") | lit("Jul") | lit("Aug") | lit("Sep") | lit("Oct") | lit("Nov") | lit("Dec");
        rfc1123_date          = wkday > char_(',') > SP > date1 > SP > time > SP > lit("GMT");
        SIP_date              = rfc1123_date;
        Date = lit("Date") > HCOLON > SIP_date;

        Error_Info            = lit("Error-Info") > HCOLON > error_uri > *(COMMA > error_uri);
        error_uri             = LAQUOT > absoluteURI > RAQUOT > *(SEMI > generic_param);

        Expires               = lit("Expires") > HCOLON > delta_seconds;
        From                  = (lit("From") | char_('f')) > HCOLON > from_spec;
        from_spec             = (name_addr | addr_spec) > *(SEMI > from_param);
        from_param            = tag_param | generic_param;
        tag_param             = lit("tag") > EQUAL > token;

        In_Reply_To           = lit("In-Reply-To") > HCOLON > callid > *(COMMA > callid);

        Max_Forwards          = lit("Max-Forwards") > HCOLON > +DIGIT;

        MIME_Version          = lit("MIME-Version") > HCOLON > +DIGIT > '.' > +DIGIT;

        Min_Expires           = lit("Min-Expires") > HCOLON > delta_seconds;

        Organization          = lit("Organization") > HCOLON > -TEXT_UTF8_TRIM;

        Priority              = lit("Priority") > HCOLON > priority_value;
        priority_value        = lit("emergency") | lit("urgent") | lit("normal") | lit("non_urgent") | other_priority;
        other_priority        = token;

        Proxy_Authenticate    = lit("Proxy-Authenticate") > HCOLON > challenge;
        challenge             = (lit("Digest") > LWS > digest_cln > *(COMMA > digest_cln)) | other_challenge;
        other_challenge       = auth_scheme > LWS > auth_param > *(COMMA > auth_param);
        digest_cln            = realm | domain | nonce | opaque | stale | algorithm | qop_options | auth_param;
        realm                 = lit("realm") > EQUAL > realm_value;
        realm_value           = quoted_string;
        domain                = lit("domain") > EQUAL > LDQUOT > URI > *(+SP > URI) > RDQUOT;
        URI                   = absoluteURI | abs_path;
        nonce                 = lit("nonce") > EQUAL > nonce_value;
        
        opaque                = lit("opaque") > EQUAL > quoted_string;
        stale                 = lit("stale") > EQUAL > (lit("true") | lit("false"));
        algorithm             = lit("algorithm") > EQUAL > (lit("MD5") | lit("MD5_sess") | token);
        qop_options           = lit("qop") > EQUAL > LDQUOT > qop_value > *(char_(',') > qop_value) > RDQUOT;
        qop_value             = lit("auth") | lit("auth_int") | token;

        Proxy_Authorization   = lit("Proxy-Authorization") > HCOLON > credentials;

        Proxy_Require         = lit("Proxy-Require") > HCOLON > option_tag > *(COMMA > option_tag);
        option_tag            = token;

        Record_Route          = lit("Record-Route") > HCOLON > rec_route > *(COMMA > rec_route);
        rec_route             = name_addr > *(SEMI > rr_param);
        rr_param              = generic_param;

        Reply_To              = lit("Reply-To") > HCOLON > rplyto_spec;
        rplyto_spec           = (name_addr | addr_spec) > *(SEMI > rplyto_param);
        rplyto_param          = generic_param;
        Require               = lit("Require") > HCOLON > option_tag > *(COMMA > option_tag);

        Retry_After           = lit("Retry-After") > HCOLON > delta_seconds > -comment > *(SEMI > retry_param);

        retry_param           = (lit("duration") > EQUAL > delta_seconds) | generic_param;

        Route                 = lit("Route") > HCOLON > route_param > *(COMMA > route_param);
        route_param           = name_addr > *(SEMI > rr_param);

        Server            = "Server" > HCOLON > server_val > *(LWS > server_val);
        server_val        = product | comment;
        product           = token > -(SLASH > product_version);
        product_version   = token;

        Subject           = (lit("Subject") | char_('s')) > HCOLON > -TEXT_UTF8_TRIM;

        Supported         = (lit("Supported") | char_('k')) > HCOLON > -(option_tag > *(COMMA > option_tag));
        Timestamp         = lit("Timestamp") > HCOLON > +(DIGIT) > -(char_('.') > *(DIGIT)) > -(LWS > delay);
        delay             = *DIGIT > -(char_('.') > *DIGIT);
        To                = (lit("To") | char_('t')) > HCOLON > (name_addr | addr_spec) >> *(SEMI > to_param);
        to_param          = tag_param | generic_param;
        Unsupported       = lit("Unsupported") > HCOLON > option_tag > *(COMMA > option_tag);
        User_Agent        = lit("User-Agent") > HCOLON > server_val > *(LWS > server_val);

        Via.name("name");
        Via               = ( lit("Via") | char_('v') ) > HCOLON > via_parm >> *(COMMA >> via_parm);
        via_parm.name("name");
        via_parm          = sent_protocol > LWS > sent_by > *(SEMI > via_params);
        via_params        = via_ttl | via_maddr | via_received | via_branch | via_extension;
        via_ttl           = lit("ttl") > EQUAL > ttl;
        via_maddr         = lit("maddr") > EQUAL > host;
        via_received      = lit("received") > EQUAL > (IPv4address | IPv6address);
        via_branch        = lit("branch") > EQUAL > token;
        via_extension     = generic_param;
        sent_protocol     = protocol_name > SLASH > protocol_version > SLASH > transport;
        protocol_name     = lit("SIP") | token;
        protocol_version  = token;
        transport         = lit("UDP") | lit("TCP") | lit("TLS") | lit("SCTP") | other_transport;
        sent_by           = host > -(COLON > port);
        ttl               = repeat(1, 3)[DIGIT]; // 0 to 255
                          
        Warning           =  lit("Warning") > HCOLON > warning_value > *(COMMA > warning_value);
        warning_value     =  warn_code > SP > warn_agent > SP > warn_text;
        warn_code         =  repeat(3,3)[DIGIT];
        warn_agent        =  hostport | pseudonym;

        warn_text          =  quoted_string;
        pseudonym          =  token;
        WWW_Authenticate   =  lit("WWW-Authenticate") > HCOLON > challenge;
        extension_header   =  header_name > HCOLON > header_value;
        header_name        =  token;
        header_value       =  *(TEXT_UTF8char | UTF8_CONT | LWS);
        message_body       =  *OCTET;

        root = SIP_message;

        on_error<fail>
          (
          root
          , std::cout
          << val("Error! Expecting ")
          << qi::_4                               // what failed?
          << val(" here: \"")
          << construct<std::string>(qi::_3, qi::_2)   // iterators to error-pos, end
          << val("\"")
          << std::endl
          );
      }
    };
  }
}

#endif // SIP0X_PARSER_SIPGRAMMAR_HPP__