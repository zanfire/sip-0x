#if !defined(SIP0X_PARSER_TOKENSIPMESSAGEHEADER_DATE_HPP__)
#define SIP0X_PARSER_TOKENSIPMESSAGEHEADER_DATE_HPP__

#include "parser/base/TokenAbstract.hpp"
#include "parser/base/Operators.hpp"
#include "parser/base/TokenRegex.hpp"



#include "parser/sip/TokenSIPMethod.hpp"
#include "parser/sip/messageheaders/TokenSIPMessageHeader_base.hpp"

namespace sip0x
{
  namespace Parser
  {
    // Date          =  "Date" HCOLON SIP-date
    // SIP-date      =  rfc1123-date
    // rfc1123-date  =  wkday "," SP date1 SP time SP "GMT"
    // date1         =  2DIGIT SP month SP 4DIGIT
    //                  ; day month year (e.g., 02 Jun 1982)
    // time          =  2DIGIT ":" 2DIGIT ":" 2DIGIT
    //                  ; 00:00:00 - 23:59:59
    // wkday         =  "Mon" / "Tue" / "Wed"
    //                  / "Thu" / "Fri" / "Sat" / "Sun"
    // month         =  "Jan" / "Feb" / "Mar" / "Apr"
    //                  / "May" / "Jun" / "Jul" / "Aug"
    //                  / "Sep" / "Oct" / "Nov" / "Dec"
    class TokenSIPMessageHeader_Date : public TokenSIPMessageHeader_base<Sequence<TokenRegex, TokenLWS, TokenSIPMethod>> {

    protected:

    public:
      //
      TokenSIPMessageHeader_Date() : TokenSIPMessageHeader_base("Date", "Date",
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

#endif // SIP0X_PARSER_TOKENSIPMESSAGEHEADER_DATE_HPP__
