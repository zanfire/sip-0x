#if !defined(SIP0X_PARSER_REGEXCONSTSTRINGS_HPP__)
#define SIP0X_PARSER_REGEXCONSTSTRINGS_HPP__

#include <string>

namespace sip0x
{
  namespace parser
  {
    struct RegexConstStrings {
      
      const static std::string token;
      //const static std::string separators;
      const static std::string word;

      const static std::string reserved;
      const static std::string unreserved;
      const static std::string escaped;
      
      const static std::string hnv_unreserved;

      const static std::string qvalue;

      const static std::string sip_user_unreserved;
      const static std::string sip_password_unreserved;
      const static std::string sip_param_unreserved;

      const static std::string qdtext;
      const static std::string quoted_pair;

      const static std::string UTF8_CONT;
      const static std::string UTF8_NONASCII;
      const static std::string TEXT_UTF8char;
      const static std::string TEXT_UTF8_TRIM;

      const static std::string SP;
      const static std::string HTAB;
      const static std::string WSP;
      const static std::string LWS;
      const static std::string SWS;
      const static std::string CRLF;
      const static std::string DQUOTE;

      const static std::string STAR;
      const static std::string SLASH;
      const static std::string EQUAL;
      const static std::string LPAREN;
      const static std::string RPAREN;
      const static std::string RAQUOT;
      const static std::string LAQUOT;
      const static std::string COMMA;
      const static std::string SEMI;
      const static std::string COLON;
      const static std::string LDQUOT;
      const static std::string RDQUOT;

      const static std::string HCOLON;
    };

  }
}

#endif // SIP0X_PARSER_REGEXCONSTSTRINGS_HPP__
