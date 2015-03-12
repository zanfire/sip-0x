#if !defined(SIP0X_PARSER_TOKENPRESETS_HPP__)
#define SIP0X_PARSER_TOKENPRESETS_HPP__

#include "parser/base/TokenRegex.hpp"
#include "parser/common/RegexConstStrings.hpp"
#include "parser/factory/FactoryContextValue.hpp"

#include <string>

namespace sip0x
{
  namespace Parser
  {
    
    class TokenDigits : public TokenRegex {
    public:
      TokenDigits() : TokenRegex("digits", "[0-9]+") {
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContextDigits();
      }
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

    class TokenSLASH : public TokenRegex {
    public:
      TokenSLASH() : TokenRegex("SLASH", RegexConstStrings::SLASH) {}
    };

    class TokenSTAR : public TokenRegex {
    public:
      TokenSTAR() : TokenRegex("STAR", RegexConstStrings::STAR) {}
    };

    class TokenCOMMA : public TokenRegex {
    public:
      TokenCOMMA() : TokenRegex("COMMA", RegexConstStrings::COMMA) {}
    };


    class TokenEQUAL : public TokenRegex {
    public:
      TokenEQUAL() : TokenRegex("EQUAL", RegexConstStrings::EQUAL) {}
    };

    class TokenSP : public TokenRegex {
    public:
      TokenSP() : TokenRegex("SP", RegexConstStrings::SP) {}
      virtual FactoryContext* create_factory(void) const override { return nullptr; }
    };


    class TokenCRLF : public TokenRegex {
    public:
      TokenCRLF() : TokenRegex("CRLF", RegexConstStrings::CRLF) {}
      virtual FactoryContext* create_factory(void) const override { return nullptr; }
    };

    class TokenWord : public TokenRegex {
    public:
      TokenWord() : TokenRegex("word", RegexConstStrings::word) {}
    };
  }
}

#endif // SIP0X_PARSER_TOKENPRESETS_HPP__
