#include "parser/common/RegexConstStrings.hpp"

#include <string>

namespace Sip0x
{
  namespace Parser
  {
    const std::string RegexConstStrings::SP = "(\\x20)";
    const std::string RegexConstStrings::HTAB = "(\\x09)";
    const std::string RegexConstStrings::CRLF = "(\\r\\n)";
    const std::string RegexConstStrings::DQUOTE = "(\\x22)";

    // LWS  =  [*WSP CRLF] 1*WSP ; linear whitespace
    // SWS  =  [LWS] ; sep whitespace
    const std::string RegexConstStrings::WSP = "(" + SP + "|" + HTAB + ")";
    const std::string RegexConstStrings::LWS = "((" + WSP + "*" + CRLF + "){0,1}" + WSP + "+)";
    const std::string RegexConstStrings::SWS = "(" + LWS + "{0,1})";

    //qvalue         =  ( "0" [ "." 0*3DIGIT ] ) / ( "1" [ "." 0*3("0") ] )
    const std::string RegexConstStrings::qvalue = "((0(.[0-9]{0,3})?)|(0(.0{0,3})?))";


    const std::string RegexConstStrings::STAR    = "(" + SWS + "\\*" + SWS + ")"; // asterisk
    const std::string RegexConstStrings::SLASH   = "(" + SWS + "/" + SWS + ")"; // slash
    const std::string RegexConstStrings::EQUAL   = "(" + SWS + "=" + SWS + ")"; // equal
    const std::string RegexConstStrings::LPAREN  = "(" + SWS + "\\(" + SWS + ")"; // left parenthesis
    const std::string RegexConstStrings::RPAREN  = "(" + SWS + "\\)" + SWS + ")"; // right parenthesis
    const std::string RegexConstStrings::RAQUOT  = "(>" + SWS + ")";       // right angle quote
    const std::string RegexConstStrings::LAQUOT  = "(" + SWS + "<)";       // left angle quote
    const std::string RegexConstStrings::COMMA   = "(" + SWS + "," + SWS + ")"; // comma
    const std::string RegexConstStrings::SEMI    = "(" + SWS + ";" + SWS + ")"; // semicolon
    const std::string RegexConstStrings::COLON   = "(" + SWS + ":" + SWS + ")"; // colon
    const std::string RegexConstStrings::LDQUOT  = "(" + SWS + DQUOTE + ")";    // open double quotation mark
    const std::string RegexConstStrings::RDQUOT  = "(" + DQUOTE + SWS + ")";    // close double quotation mark

    // HCOLON = *(SP / HTAB) ":" SWS
    const std::string RegexConstStrings::HCOLON = "(" + WSP + "*:" + SWS + ")";
    
    // TEXT-UTF8-TRIM  =  1*TEXT-UTF8char *(*LWS TEXT-UTF8char)
    // TEXT-UTF8char   =  %x21-7E / UTF8-NONASCII
    // UTF8-NONASCII   =  %xC0-DF 1UTF8-CONT
    //                 /  %xE0-EF 2UTF8-CONT
    //                 /  %xF0-F7 3UTF8-CONT
    //                 /  %xF8-Fb 4UTF8-CONT
    //                 /  %xFC-FD 5UTF8-CONT
    // UTF8-CONT       =  %x80-BF
    const std::string RegexConstStrings::UTF8_CONT = "([\\x80-\\xBF])";
    //TEXT - UTF8 - TRIM = 1 * TEXT - UTF8char *(*LWS TEXT - UTF8char)
    const std::string RegexConstStrings::UTF8_NONASCII = "(" \
       "([\\xC0-\\xDF]" + UTF8_CONT + "{1})" \
      "|([\\xE0-\\xEF]" + UTF8_CONT + "{2})" \
      "|([\\xF0-\\xF7]" + UTF8_CONT + "{3})" \
      "|([\\xF8-\\xFB]" + UTF8_CONT + "{4})" \
      "|([\\xFC-\\xFD]" + UTF8_CONT + "{5})" \
      ")";
    const std::string RegexConstStrings::TEXT_UTF8char = "(([\\x21-\\x7E])|" + UTF8_NONASCII + ")";
    // TEXT-UTF8-TRIM  =  1*TEXT-UTF8char *(*LWS TEXT-UTF8char)
    const std::string RegexConstStrings::TEXT_UTF8_TRIM = "(" + TEXT_UTF8char + "+(" + LWS + "*" + TEXT_UTF8char + "*))";

    const std::string RegexConstStrings::token = "([A-Za-z-0-9\\-_\\.\\!\\%\\*\\+`\\'\\~]+)";
    // ";" / "/" / "?" / ":" / "@" / "&" / "=" / "+" / "$" / ","
    const std::string RegexConstStrings::reserved = "([\\;\\/\\?\\:\\@\\&\\=\\+\\$\\,])";
    const std::string RegexConstStrings::unreserved = "([A-Za-z-0-9]|[\\-_\\.\\!\\~\\*\\'\\|])";
    const std::string RegexConstStrings::escaped = "(%[0-9a-fA-F][0-9a-fA-F])";

    const std::string RegexConstStrings::hnv_unreserved = "([\\[\\]\\/\\?\\:\\+\\$])";

    // word        =  1*(alphanum / "-" / "." / "!" / "%" / "*" / "_" / "+" / "`" / "'" / "~" /
    //            "(" / ")" / "<" / ">" /
    //            ":" / "\" / DQUOTE /
    //            "/" / "[" / "]" / "?" /
    //            "{" / "}" )
    const std::string RegexConstStrings::word = "([A-Za-z-0-9\\-_\\.\\!\\%\\*\\+`\\'\\~\\(\\)\\<\\>\\:\\\\\\x22\\/\\[\\]\\?\\{\\}]+)";

    // TODO: it should qdtext = LWS / %x21 / %x23 - 5B / %x5D - 7E / UTF8-NONASCII
    const std::string RegexConstStrings::qdtext = "((" + LWS + ")(\\x21)|([\\x23-\\x5B])|([\\x5D-\\x7E]))";
    // TODO: It should "\\\\((%x00-09)|(%x0B-0C)|(%x0E-7F)))";
    const std::string RegexConstStrings::quoted_pair = "\\\\(([\\x00-\\x09])|([\\x0B-\\x0C])|([\\x0E-\\x7F]))";

    const std::string RegexConstStrings::sip_user_unreserved = "([\\&=\\+\\$,;\\?/])";
    const std::string RegexConstStrings::sip_password_unreserved = "([\\&=\\+\\$,])";

    const std::string RegexConstStrings::sip_param_unreserved = "([\\[\\]/\\:\\&\\+\\$])";
  }
}
