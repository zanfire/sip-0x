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
    using ascii::char_;;
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

      qi::rule<Iterator, std::string()> LHEX;

      qi::rule<Iterator, std::string()> token;              
      qi::rule<Iterator, std::string()> separators;         
      qi::rule<Iterator, std::string()> word;       

      qi::rule<Iterator, std::string()> comment;            
      qi::rule<Iterator, std::string()> ctext;              

      qi::rule<Iterator, std::string()> quoted_string;      
      qi::rule<Iterator, std::string()> qdtext;             

      // Basic rules (from RFC 3261)
      qi::rule<Iterator, std::string()> quoted_pair;        


      qi::rule<Iterator, std::string()> SIP_URI;            
      qi::rule<Iterator, std::string()> SIPS_URI;           
      qi::rule<Iterator, std::string()> userinfo;           
      qi::rule<Iterator, std::string()> user;               
      qi::rule<Iterator, std::string()> user_unreserved;    
      qi::rule<Iterator, std::string()> password;           
      qi::rule<Iterator, std::string()> hostport;           
      qi::rule<Iterator, std::string()> host;               
      qi::rule<Iterator, std::string()> hostname;           
      qi::rule<Iterator, std::string()> domainlabel;        
      qi::rule<Iterator, std::string()> toplabel;           
      qi::rule<Iterator, std::string()> IPv4address;        
      qi::rule<Iterator, std::string()> IPv6reference;      
      qi::rule<Iterator, std::string()> IPv6address;        
      qi::rule<Iterator, std::string()> hexpart;            
      qi::rule<Iterator, std::string()> hexseq;             
      qi::rule<Iterator, std::string()> hex4;               
      qi::rule<Iterator, std::string()> port;

    
      SIPGrammar() : SIPGrammar::base_type(root)
      {
        // Initialization 
        // Core rules
        CRLF.name("CRLF");
        CRLF      = lit("\r\n");
        SP.name("SP");
        SP        = char_(' ');
        ALPHA     = char_("A-Z") | char_("a-z");
        DIGIT     = char_("0-9");
        HEXDIG    = DIGIT | char_("A-F");
        LWSP      = *(WSP | CRLF > WSP); // linear white space(past newline)
        OCTET     = char_(0x00, 0xFF); // 8 bits of data
        VCHAR     = char_(0x21, 0x7E); // visible(printing) characters
        WSP.name("WSP");
        WSP       = SP | char_(0x09); // white space
        HTAB      = char_(0x09);
        DQUOTE    = char_(0x22);

        // Basic rules
        alphanum = ALPHA | DIGIT;

        reserved      = char_(';') | char_('|') | char_('?') | char_(':') | char_('@') | char_('&') | char_('=') | char_('+') | char_('$') | char_(',');
        mark          = char_('-') | char_('_') | char_('.') | char_('!') | char_('~') | char_('*') | char_('\'') | char_('(') | char_(')');
        unreserved    = alphanum | mark;
        escaped       = char_('%') > HEXDIG > HEXDIG;

        LWS.name("LWS");
        LWS = -(*WSP >> CRLF) >> +WSP; // linear whitespace
        SWS.name("SWS");
        SWS = -LWS;  // sep whitespace
        

        STAR.name("*");
        STAR    =  SWS >> '*' >> SWS;
        SLASH.name("/");
        SLASH   =  SWS >> '/' >> SWS;
        EQUAL.name("=");
        EQUAL   =  SWS >> '=' >> SWS;
        LPAREN  =  SWS >> '(' >> SWS;
        RPAREN  =  SWS >> ')' >> SWS;
        RAQUOT.name(">");
        RAQUOT  =  '>' >> SWS;
        LAQUOT.name("<");
        LAQUOT  =  SWS >> '<';
        COMMA   =  SWS >> ',' >> SWS;
        SEMI    =  SWS >> ';' >> SWS;
        COLON.name(":");
        COLON   =  SWS >> ':' >> SWS;
        LDQUOT  =  SWS >> DQUOTE;
        RDQUOT  =  DQUOTE >> SWS;

        HCOLON.name(":");
        HCOLON = *(WSP) >> char_(':') >> SWS;

        TEXT_UTF8_TRIM  = +TEXT_UTF8char > *(*LWS > TEXT_UTF8char);
        TEXT_UTF8char   = char_(0x21, 0x7E) | UTF8_NONASCII;
        UTF8_NONASCII   = (char_(0xC0, 0xDF) > UTF8_CONT) | (char_(0xE0, 0xEF) > repeat(2, 2)[UTF8_CONT]) | (char_(0xF0, 0xF7) > repeat(3, 3)[UTF8_CONT]) | (char_(0xF8, 0xFb) > repeat(4, 4)[UTF8_CONT]) | (char_(0xFC, 0xFD) > repeat(5, 5)[UTF8_CONT]);
        UTF8_CONT       = char_(0x80, 0xBF);

        LHEX = DIGIT | char_("a-f");


        token           = +(alphanum | '-' | '.' | '!' | '%' | '*' | '_' | '+' | '`' | '\'' | '~');
        separators      = (char_('(') | char_(')') | char_('<') | char_('>') | char_('@') | char_(',') | char_(';') | char_(':') | char_('\\') | char_('\"') | char_('|') | char_('[') | char_(']') | char_('?') | char_('=') | char_('{') | char_('}') | SP | HTAB);
        word            = +(alphanum | '-' | '.' | '!' | '%' | '*' | '_' | '+' | '`' | '\'' | '~' | '(' | ')' | '<' | '>' | ':' | '\\' | '\"' | '|' | '[' | ']' | '?' | '{' | '}');

        comment         = LPAREN > *(ctext | quoted_pair | comment) > RPAREN;
        ctext           = (char_(0x21, 0x27) | char_(0x2A, 0x5B) | char_(0x5D, 0x7E)) > UTF8_NONASCII | LWS;

        quoted_string    = SWS > DQUOTE > *(qdtext | quoted_pair) > DQUOTE;
        qdtext           = LWS | char_(0x21) | char_(0x23, 0x5B) | char_(0x5D, 0x7E) | UTF8_NONASCII;

        quoted_pair = '\"' > (char_(0x00, 0x09) | char_(0x0B, 0x0C) | char_(0x0E, 0x7F));
        
        SIP_URI = lit("sip:") > -userinfo > hostport; // >> uri_parameters >> -headers;
        SIPS_URI = lit("sips:") > -userinfo > hostport; // >> uri_parameters >> -headers;
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

        

        root = qi::eps > SIP_URI;

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