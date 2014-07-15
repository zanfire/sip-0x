#if !defined(SIP0X_PARSER_TOKENPRESETS_HPP__)
#define SIP0X_PARSER_TOKENPRESETS_HPP__

#include "parser/base/TokenRegex.hpp"
#include "parser/common/RegexConstStrings.hpp"

#include <string>

namespace Sip0x
{
  namespace Parser
  {
    
    class TokenDigits : public TokenRegex {
    public:
      TokenDigits() : TokenRegex("digits", "[0-9]+") {}
    };

    class TokenLWS : public TokenRegex {
    public:
      TokenLWS() : TokenRegex("LWS", RegexConstStrings::LWS) {}
    };

    class TokenHCOLON : public TokenRegex {
    public:
      TokenHCOLON() : TokenRegex("HCOLON", RegexConstStrings::HCOLON) {}
    };

    class TokenLAQUOT : public TokenRegex {
    public:
      TokenLAQUOT() : TokenRegex("LAQUOT", RegexConstStrings::LAQUOT) {}
    };

    class TokenRAQUOT : public TokenRegex {
    public:
      TokenRAQUOT() : TokenRegex("RAQUOT", RegexConstStrings::RAQUOT) {}
    };

    class TokenSEMI : public TokenRegex {
    public:
      TokenSEMI() : TokenRegex("SEMI", RegexConstStrings::SEMI) {}
    };

    class TokenCRLF : public TokenRegex {
    public:
      TokenCRLF() : TokenRegex("CRLF", RegexConstStrings::CRLF) {}
    };

    class TokenWord : public TokenRegex {
    public:
      TokenWord() : TokenRegex("word", RegexConstStrings::word) {}
    };
  }
}

#endif // SIP0X_PARSER_TOKENPRESETS_HPP__
