#if !defined(SIP0X_PARSER_PARSER_HPP__)
#define SIP0X_PARSER_PARSER_HPP__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace Sip0x 
{
  namespace Parser 
  {

    void print(double const& i)
    {
      std::cout << i << std::endl;
    }

    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last)
    {
      using qi::double_;
      using qi::phrase_parse;
      using ascii::space;

      bool r = phrase_parse(
        first,                          /*< start iterator >*/
        last,                           /*< end iterator >*/
        double_[&print] >> *(',' >> double_[&print]),   /*< the parser >*/
        space                           /*< the skip-parser >*/
        );
      if (first != last) // fail if we did not get a full match
        return false;
      return r;
    }



    /*
    SIP-message    =  Request / Response
    Request        =  Request-Line
                      *( message-header )
                      CRLF
    Request-Line   =  Method SP Request-URI SP SIP-Version CRLF
    */
  }
}

#endif // SIP0X_PARSER_PARSER_HPP__
