#if !defined(SIP0X_PARSER_OCCURRENCE_HPP__)
#define SIP0X_PARSER_OCCURRENCE_HPP__

#include "parser/tokens/TokenContainer.hpp"

namespace sip0x
{
  namespace parser
  {
    template<class T>
    class Occurrence : public TokenContainer<T> {
    protected:
      int _min;
      int _max;

    public:
      Occurrence(const T& f, int min = 0, int max = -1, bool disable_factory = false) : TokenContainer<T>("Occurrence", f, disable_factory), _min(min), _max(max) {
        this->_name += "." + f.get_name(); // + "[" + std::string(_min) + "," + std::string(_max) + "]";
#if defined(ENABLE_PARSER_LOGGING)
        _logger = LoggerFactory::get_logger("sip0x.Parser.Occurrence");
#endif
      }

    protected: 
      virtual ParserResult handle_read(sip0x::utils::InputTokenStream& iss, FactoryContext* ctx) const override {
        
        int occurrence = 0;
        while ((_max >= 0 && occurrence <= _max) || _max == -1) {
          ParserResult output = this->_token.read(iss, ctx);

          if (!output.success()) {
            break;
          }
          else {
            occurrence++;
          }
          // Stop reading when match the max.
          if (occurrence == _max) {
            break;
          }
        }

        if (occurrence >= _min && (occurrence <= _max || _max == -1)) {
#if defined(ENABLE_PARSER_LOGGING)
          LOG_DEBUG(_logger, "Successes Occurrence@%p, occurrence: %d in range [%d - %d].", this, occurrence, _min, _max);
#endif
          return ParserResult(true, 0, 0);
        }
        else {
#if defined(ENABLE_PARSER_LOGGING)
          LOG_DEBUG(_logger, "Failed Occurrence@%p, occurrence: %d out of range [%d - %d].", this, occurrence, _min, _max);
#endif
          return ParserResult();
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_OCCURRENCE_HPP__
